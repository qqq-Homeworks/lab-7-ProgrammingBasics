#include "header.h"

void encription(char *file_name, char *key_file_name, bool flag) {
    std::fstream original_file;
    original_file.open(file_name);
    original_file.seekg(std::ios_base::beg, std::ios_base::end);
    long int file_len = original_file.tellg();
    original_file.seekg(0);
    char *text = new char[file_len];
    original_file.read(text, file_len + 1);
    original_file.close();

    std::fstream key_file;
    key_file.open(key_file_name);
    key_file.seekg(std::ios_base::beg, std::ios_base::end);
    long int key_len = key_file.tellg();
    key_file.seekg(0);
    char *key = new char[key_len];
    int count = 0;
    int space = 0;
    for (int i = 0; i < key_len; ++i) {
        char tmp = key_file.peek();
        if (!std::ispunct(tmp) && !std::isspace(tmp)) {
            key[count] += key_file.get();
            space = 0;
        } else {
            if (space != 0) {
                --count;
            } else {
                ++space;

            }
            ++count;
            key_file.get();
        }
    }
    std::fstream encryption;
    encryption.open("encrypted.txt", std::ios::out);

    long int i = 0;
    int stat[256][256];
    int k = flag ? 1 : -1;
    for (; i < file_len; ++i) {
        stat[text[i]][k * key[i % count]]++;
        text[i] += k * key[i % count];
    }
    std::cout << "По какому символу хотите получить статистику: " << std::endl;
    char ch;
    std::cin >> ch;
    int sim = (int) ch;
    std::cout << "Символ " << ch << " был закодирован: " << std::endl;
    for (int i = 0; i < 256; i++) {
        if (stat[sim][i] != 0) {
            std::cout << "Символом " << " " << char(i) << " " << stat[sim][i] << std::endl;
        }
    }
    encryption.write(text, file_len);
    encryption.close();
}
