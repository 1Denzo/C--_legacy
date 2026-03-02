#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // Проверка аргументов командной строки
    if (argc != 4) {
        std::cerr << "Использование: " << argv[0] << " <входной_файл> <выходной_файл> <ключ>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string key = argv[3];

    // Проверка, что ключ не пустой
    if (key.empty()) {
        std::cerr << "Ошибка: ключ шифрования не может быть пустым" << std::endl;
        return 1;
    }

    // Открытие входного файла для чтения в бинарном режиме
    std::ifstream in(inputFile, std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Ошибка: не удалось открыть входной файл " << inputFile << std::endl;
        return 1;
    }

    // Открытие выходного файла для записи в бинарном режиме
    std::ofstream out(outputFile, std::ios::binary);
    if (!out.is_open()) {
        std::cerr << "Ошибка: не удалось создать выходной файл " << outputFile << std::endl;
        return 1;
    }

    // Шифрование данных
    char c;
    size_t keyIndex = 0;
    size_t keyLength = key.length();

    while (in.get(c)) {
        // XOR шифрование: c = c ^ key[keyIndex]
        char encrypted = c ^ key[keyIndex];
        out.put(encrypted);

        // Циклический переход к следующему символу ключа
        keyIndex = (keyIndex + 1) % keyLength;
    }

    // Проверка на ошибки при чтении/записи
    if (in.bad()) {
        std::cerr << "Ошибка при чтении входного файла" << std::endl;
        return 1;
    }

    if (out.bad()) {
        std::cerr << "Ошибка при записи в выходной файл" << std::endl;
        return 1;
    }

    std::cout << "Файл успешно зашифрован!" << std::endl;
    std::cout << "Размер ключа: " << keyLength << " символов" << std::endl;

    return 0;
}
// Использование
// ./encryptor input.txt encrypted.txt mysecretkey

// Для расшифровки (используйте тот же ключ)
// ./encryptor encrypted.txt decrypted.txt mysecretkey
