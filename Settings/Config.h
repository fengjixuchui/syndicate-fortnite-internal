#include "../stdafx.h"

inline void SaveConfig() {
    const char* path = xor_a("C:\\Users\\Public\\config.dat");

    FILE* file = LI_FN(fopen).get()(path, "wb");
    if (file) {
        size_t written = LI_FN(fwrite).get()(&Config, sizeof(Config), 1, file);
        LI_FN(fflush).get()(file); // Ensure data is written to disk
        LI_FN(fclose).get()(file);    
    }
}

inline void LoadConfig() {
    const char* path = xor_a("C:\\Users\\Public\\config.dat");
    FILE* file = LI_FN(fopen).get()(path, "rb");
    if (file) {
        LI_FN(fseek).get()(file, 0, SEEK_END);
        long size = LI_FN(ftell).get()(file);

        if (size == sizeof(Config)) {
            LI_FN(fseek).get()(file, 0, SEEK_SET);
            size_t read = LI_FN(fread).get()(&Config, sizeof(Config), 1, file);         
        }
        LI_FN(fclose).get()(file);
    }
}