#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>

// Перечисление состояний потоков
enum class StreamState {
    CLOSED,
    OPEN,
    ERROR,
    EOF_STATE
};

// Базовый класс с управлением состоянием
class StatefulStream {
protected:
    StreamState state;
    std::string filename;
    
public:
    StatefulStream(const std::string& name) : state(StreamState::CLOSED), filename(name) {}
    virtual ~StatefulStream() = default;
    
    // Методы для работы с состоянием
    virtual bool open() = 0;
    virtual void close() = 0;
    
    StreamState getState() const { return state; }
    bool isOpen() const { return state == StreamState::OPEN; }
    bool isError() const { return state == StreamState::ERROR; }
    bool isEof() const { return state == StreamState::EOF_STATE; }
    
    virtual std::string getStateString() const {
        switch(state) {
            case StreamState::CLOSED: return "ЗАКРЫТ";
            case StreamState::OPEN: return "ОТКРЫТ";
            case StreamState::ERROR: return "ОШИБКА";
            case StreamState::EOF_STATE: return "КОНЕЦ ФАЙЛА";
            default: return "НЕИЗВЕСТНО";
        }
    }
    
    virtual void reset() {
        close();
        state = StreamState::CLOSED;
    }
};

// Класс для входного потока с управлением состоянием
class InputFileStream : public StatefulStream {
private:
    std::ifstream stream;
    
public:
    InputFileStream(const std::string& name) : StatefulStream(name) {}
    
    bool open() override {
        stream.open(filename, std::ios::binary);
        if (stream.is_open()) {
            state = StreamState::OPEN;
            return true;
        } else {
            state = StreamState::ERROR;
            return false;
        }
    }
    
    void close() override {
        if (stream.is_open()) {
            stream.close();
        }
        state = StreamState::CLOSED;
    }
    
    // Метод для чтения с изменением состояния
    bool readByte(char& c) {
        if (state != StreamState::OPEN) {
            state = StreamState::ERROR;
            return false;
        }
        
        stream.get(c);
        
        if (stream.eof()) {
            state = StreamState::EOF_STATE;
            return false;
        } else if (stream.fail()) {
            state = StreamState::ERROR;
            return false;
        }
        
        return true;
    }
    
    // Метод для чтения блока данных
    size_t readBytes(char* buffer, size_t maxSize) {
        if (state != StreamState::OPEN) {
            state = StreamState::ERROR;
            return 0;
        }
        
        stream.read(buffer, maxSize);
        size_t read = stream.gcount();
        
        if (stream.eof()) {
            state = StreamState::EOF_STATE;
        } else if (stream.fail()) {
            state = StreamState::ERROR;
        }
        
        return read;
    }
    
    // Переопределение метода сброса
    void reset() override {
        StatefulStream::reset();
        stream.clear(); // Сброс флагов состояния потока
    }
};

// Класс для выходного потока с управлением состоянием
class OutputFileStream : public StatefulStream {
private:
    std::ofstream stream;
    
public:
    OutputFileStream(const std::string& name) : StatefulStream(name) {}
    
    bool open() override {
        stream.open(filename, std::ios::binary);
        if (stream.is_open()) {
            state = StreamState::OPEN;
            return true;
        } else {
            state = StreamState::ERROR;
            return false;
        }
    }
    
    void close() override {
        if (stream.is_open()) {
            stream.flush();
            stream.close();
        }
        state = StreamState::CLOSED;
    }
    
    // Метод для записи с изменением состояния
    bool writeByte(char c) {
        if (state != StreamState::OPEN) {
            state = StreamState::ERROR;
            return false;
        }
        
        stream.put(c);
        
        if (stream.fail()) {
            state = StreamState::ERROR;
            return false;
        }
        
        return true;
    }
    
    // Метод для записи блока данных
    size_t writeBytes(const char* buffer, size_t size) {
        if (state != StreamState::OPEN) {
            state = StreamState::ERROR;
            return 0;
        }
        
        stream.write(buffer, size);
        
        if (stream.fail()) {
            state = StreamState::ERROR;
            return 0;
        }
        
        return size;
    }
    
    // Принудительная запись буфера
    bool flush() {
        if (state != StreamState::OPEN) {
            return false;
        }
        
        stream.flush();
        return !stream.fail();
    }
    
    void reset() override {
        StatefulStream::reset();
        stream.clear();
    }
};

// Класс ключа с состоянием
class EncryptionKey {
private:
    std::string key;
    size_t position;
    bool valid;
    
public:
    EncryptionKey(const std::string& k) : key(k), position(0), valid(true) {
        if (key.empty()) {
            valid = false;
            throw std::invalid_argument("Ключ не может быть пустым");
        }
    }
    
    // Методы для работы с состоянием ключа
    char getNextChar() {
        if (!valid || key.empty()) {
            return 0;
        }
        
        char result = key[position];
        position = (position + 1) % key.length();
        return result;
    }
    
    void reset() {
        position = 0;
        valid = true;
    }
    
    void invalidate() {
        valid = false;
    }
    
    bool isValid() const { return valid; }
    size_t getLength() const { return key.length(); }
    size_t getPosition() const { return position; }
    
    std::string getStateString() const {
        if (!valid) return "НЕДЕЙСТВИТЕЛЕН";
        return "АКТИВЕН (позиция: " + std::to_string(position) + ")";
    }
};

// Класс шифровальщика с состоянием
class XorEncryptor {
private:
    EncryptionKey& key;
    size_t bytesProcessed;
    bool processing;
    
public:
    XorEncryptor(EncryptionKey& k) : key(k), bytesProcessed(0), processing(false) {}
    
    // Методы для управления состоянием шифрования
    void start() {
        processing = true;
        bytesProcessed = 0;
        key.reset();
    }
    
    void stop() {
        processing = false;
    }
    
    char process(char input) {
        if (!processing || !key.isValid()) {
            return input;
        }
        
        char result = input ^ key.getNextChar();
        bytesProcessed++;
        return result;
    }
    
    size_t processBuffer(const char* input, char* output, size_t size) {
        if (!processing || !key.isValid()) {
            return 0;
        }
        
        for (size_t i = 0; i < size; i++) {
            output[i] = input[i] ^ key.getNextChar();
        }
        
        bytesProcessed += size;
        return size;
    }
    
    bool isProcessing() const { return processing; }
    size_t getBytesProcessed() const { return bytesProcessed; }
    
    void reset() {
        processing = false;
        bytesProcessed = 0;
        key.reset();
    }
    
    std::string getStateString() const {
        std::string status = processing ? "РАБОТАЕТ" : "ОСТАНОВЛЕН";
        return status + " (обработано: " + std::to_string(bytesProcessed) + " байт)";
    }
};

// Главный класс приложения с конечным автоматом
class FileEncryptorApp {
private:
    enum class AppState {
        INIT,
        ARGS_CHECK,
        FILES_OPEN,
        ENCRYPTING,
        COMPLETED,
        ERROR
    };
    
    AppState state;
    std::unique_ptr<InputFileStream> input;
    std::unique_ptr<OutputFileStream> output;
    std::unique_ptr<EncryptionKey> key;
    std::unique_ptr<XorEncryptor> encryptor;
    
    std::string inputFile;
    std::string outputFile;
    std::string keyStr;
    
    void printState() {
        std::cout << "\n=== Состояние приложения ===\n";
        std::cout << "AppState: ";
        switch(state) {
            case AppState::INIT: std::cout << "ИНИЦИАЛИЗАЦИЯ"; break;
            case AppState::ARGS_CHECK: std::cout << "ПРОВЕРКА АРГУМЕНТОВ"; break;
            case AppState::FILES_OPEN: std::cout << "ОТКРЫТИЕ ФАЙЛОВ"; break;
            case AppState::ENCRYPTING: std::cout << "ШИФРОВАНИЕ"; break;
            case AppState::COMPLETED: std::cout << "ЗАВЕРШЕНО"; break;
            case AppState::ERROR: std::cout << "ОШИБКА"; break;
        }
        std::cout << "\n";
        
        if (input) {
            std::cout << "Входной поток: " << input->getStateString() << "\n";
        }
        if (output) {
            std::cout << "Выходной поток: " << output->getStateString() << "\n";
        }
        if (key) {
            std::cout << "Ключ: " << key->getStateString() << "\n";
        }
        if (encryptor) {
            std::cout << "Шифровальщик: " << encryptor->getStateString() << "\n";
        }
        std::cout << "===========================\n\n";
    }
    
    bool validateArgs(int argc, char* argv[]) {
        state = AppState::ARGS_CHECK;
        
        if (argc != 4) {
            std::cerr << "Использование: " << argv[0] 
                      << " <входной_файл> <выходной_файл> <ключ>" << std::endl;
            state = AppState::ERROR;
            return false;
        }
        
        inputFile = argv[1];
        outputFile = argv[2];
        keyStr = argv[3];
        
        return true;
    }
    
    bool openFiles() {
        state = AppState::FILES_OPEN;
        
        input = std::make_unique<InputFileStream>(inputFile);
        output = std::make_unique<OutputFileStream>(outputFile);
        
        if (!input->open()) {
            std::cerr << "Ошибка: не удалось открыть входной файл\n";
            state = AppState::ERROR;
            return false;
        }
        
        if (!output->open()) {
            std::cerr << "Ошибка: не удалось создать выходной файл\n";
            input->close();
            state = AppState::ERROR;
            return false;
        }
        
        return true;
    }
    
    bool encryptWithState() {
        state = AppState::ENCRYPTING;
        
        // Использование буферизованного чтения/записи
        const size_t BUFFER_SIZE = 4096;
        std::vector<char> inBuffer(BUFFER_SIZE);
        std::vector<char> outBuffer(BUFFER_SIZE);
        
        encryptor->start();
        
        while (true) {
            // Чтение блока данных
            size_t bytesRead = input->readBytes(inBuffer.data(), BUFFER_SIZE);
            
            if (input->isError()) {
                std::cerr << "Ошибка при чтении файла\n";
                state = AppState::ERROR;
                return false;
            }
            
            if (bytesRead == 0) {
                break; // Конец файла
            }
            
            // Шифрование блока
            encryptor->processBuffer(inBuffer.data(), outBuffer.data(), bytesRead);
            
            // Запись блока
            size_t bytesWritten = output->writeBytes(outBuffer.data(), bytesRead);
            
            if (output->isError() || bytesWritten != bytesRead) {
                std::cerr << "Ошибка при записи файла\n";
                state = AppState::ERROR;
                return false;
            }
            
            // Принудительная запись буфера после каждого блока
            output->flush();
        }
        
        encryptor->stop();
        return true;
    }
    
public:
    FileEncryptorApp() : state(AppState::INIT) {}
    
    int run(int argc, char* argv[]) {
        try {
            printState();
            
            if (!validateArgs(argc, argv)) {
                printState();
                return 1;
            }
            printState();
            
            // Создание ключа
            key = std::make_unique<EncryptionKey>(keyStr);
            encryptor = std::make_unique<XorEncryptor>(*key);
            printState();
            
            if (!openFiles()) {
                printState();
                return 1;
            }
            printState();
            
            // Шифрование
            bool success = encryptWithState();
            
            // Закрытие файлов
            input->close();
            output->close();
            
            if (success) {
                state = AppState::COMPLETED;
                std::cout << "✅ Файл успешно зашифрован!\n";
                std::cout << "Размер ключа: " << key->getLength() << " символов\n";
                std::cout << "Обработано байт: " << encryptor->getBytesProcessed() << "\n";
            } else {
                state = AppState::ERROR;
            }
            
            printState();
            return success ? 0 : 1;
            
        } catch (const std::exception& e) {
            state = AppState::ERROR;
            std::cerr << "❌ Ошибка: " << e.what() << std::endl;
            printState();
            return 1;
        }
    }
};

int main(int argc, char* argv[]) {
    FileEncryptorApp app;
    return app.run(argc, argv);
}