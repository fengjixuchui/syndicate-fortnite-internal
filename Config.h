#include "../stdafx.h"

inline void SaveConfig(std::string number)
{
	std::string path = xor_a("C:\\Users\\Public\\config") + number + xor_a(".dat");
	auto file = fopen(path.c_str(), xor_a("wb"));
	if (file) {
		fwrite(&Config, sizeof(vars), 1, file);
		fclose(file);
	}
}
inline auto LoadConfig(std::string number) -> void
{
	std::string path = xor_a("C:\\Users\\Public\\config") + number + xor_a(".dat");
	auto file = fopen(path.c_str(), xor_a("rb"));
	if (file) {
		fseek(file, 0, SEEK_END);
		auto size = ftell(file);

		if (size == sizeof(vars)) {
			fseek(file, 0, SEEK_SET);
			fread(&vars, sizeof(vars), 1, file);
			fclose(file);
		}
		else {
			fclose(file);

		}
	}
}