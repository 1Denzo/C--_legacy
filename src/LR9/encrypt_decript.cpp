#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>

// Базовый абстрактный класс для потоков
class Stream {
protected:
    std::string filename;
    bool isOpen;

public:
    Stream(const std::string& name) : filename(name), isOpen(false) {}
    virtual ~Stream() = default;
    
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool isOpened() const { return isOpen; }
    virtual std::string getFilename() const { return filename; }
};

// Класс для входного файлового потока
class InputFileStream : public Stream {
private:
    std::ifstream stream;

public:
    InputFileStream(const std::string& name) : Stream(name) {}
    
    bool open() override {
        stream.open(filename, std::ios::binary);
        isOpen = stream.is_open();
        return isOpen;
    }
    
    void close() override {
        if (stream.is_open()) {
            stream.close();
        }
        isOpen = false;
    }
    
    bool get(char& c) {
        return static_cast<bool>(stream.get(c));
    }
    
    bool isBad() const {
        return stream.bad();
    }
    
    bool isEof() const {
        return stream.eof();
    }
};

// Класс для выходного файлового потока
class OutputFileStream : public Stream {
private:
    std::ofstream stream;

public:
    OutputFileStream(const std::string& name) : Stream(name) {}
    
    bool open() override {
        stream.open(filename, std::ios::binary);
        isOpen = stream.is_open();
        return isOpen;
    }
    
    void close() override {
        if (stream.is_open()) {
            stream.close();
        }
        isOpen = false;
    }
    
    void put(char c) {
        stream.put(c);
    }
    
    bool isBad() const {
        return stream.bad();
    }
};

// Класс для ключа шифрования
class EncryptionKey {
private:
    std::string key;
    size_t currentIndex;

public:
    EncryptionKey(const std::string& k) : key(k), currentIndex(0) {
        if (key.empty()) {
            throw std::invalid_argument("Ключ шифрования не может быть пустым");
        }
    }
    
    char getNextChar() {
        char result = key[currentIndex];
        currentIndex = (currentIndex + 1) % key.length();
        return result;
    }
    
    size_t getLength() const {
        return key.length();
    }
    
    void reset() {
        currentIndex = 0;
    }
};

// Класс для шифрования XOR
class XorEncryptor {
private:
    EncryptionKey& key;

public:
    XorEncryptor(EncryptionKey& k) : key(k) {}
    
    char encrypt(char input) {
        return input ^ key.getNextChar();
    }
    
    char decrypt(char input) {
        // Для XOR шифрования и дешифрование одинаковы
        return input ^ key.getNextChar();
    }
};

// Основной класс приложения
class FileEncryptorApp {
private:
    std::unique_ptr<InputFileStream> input;
    std::unique_ptr<OutputFileStream> output;
    std::unique_ptr<EncryptionKey> key;
    std::unique_ptr<XorEncryptor> encryptor;

    void printUsage(const char* programName) {
        std::cerr << "Использование: " << programName 
                  << " <входной_файл> <выходной_файл> <ключ>" << std::endl;
    }

    bool validateArguments(int argc, char* argv[]) {
        if (argc != 4) {
            printUsage(argv[0]);
            return false;
        }
        return true;
    }

    bool openFiles(const std::string& inputFile, const std::string& outputFile) {
        input = std::make_unique<InputFileStream>(inputFile);
        output = std::make_unique<OutputFileStream>(outputFile);
        
        if (!input->open()) {
            std::cerr << "Ошибка: не удалось открыть входной файл " 
                      << inputFile << std::endl;
            return false;
        }
        
        if (!output->open()) {
            std::cerr << "Ошибка: не удалось создать выходной файл " 
                      << outputFile << std::endl;
            input->close();
            return false;
        }
        
        return true;
    }

    bool processEncryption() {
        char c;
        bool success = true;
        key->reset(); // Сброс индекса ключа перед началом
        
        while (input->get(c)) {
            char encrypted = encryptor->encrypt(c);
            output->put(encrypted);
        }
        
        // Проверка на ошибки
        if (input->isBad()) {
            std::cerr << "Ошибка при чтении входного файла" << std::endl;
            success = false;
        }
        
        if (output->isBad()) {
            std::cerr << "Ошибка при записи в выходной файл" << std::endl;
            success = false;
        }
        
        return success;
    }

    void printResults(bool success) {
        if (success) {
            std::cout << "Файл успешно зашифрован!" << std::endl;
            std::cout << "Размер ключа: " << key->getLength() << " символов" << std::endl;
        }
    }

public:
    int run(int argc, char* argv[]) {
        try {
            // Проверка аргументов
            if (!validateArguments(argc, argv)) {
                return 1;
            }

            std::string inputFile = argv[1];
            std::string outputFile = argv[2];
            std::string keyStr = argv[3];

            // Создание ключа (может выбросить исключение)
            key = std::make_unique<EncryptionKey>(keyStr);
            
            // Создание шифровальщика
            encryptor = std::make_unique<XorEncryptor>(*key);

            // Открытие файлов
            if (!openFiles(inputFile, outputFile)) {
                return 1;
            }

            // Шифрование данных
            bool success = processEncryption();

            // Закрытие файлов
            input->close();
            output->close();

            // Вывод результатов
            printResults(success);

            return success ? 0 : 1;

        } catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
            return 1;
        } catch (const std::exception& e) {
            std::cerr << "Непредвиденная ошибка: " << e.what() << std::endl;
            return 1;
        }
    }
};

// Точка входа в программу
int main(int argc, char* argv[]) {
    FileEncryptorApp app;
    return app.run(argc, argv);
}