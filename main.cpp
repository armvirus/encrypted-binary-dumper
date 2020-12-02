#include "stdafx.hpp"

std::string hex_to_string(std::uint8_t hex) 
{
	char hex_string[4 * sizeof(std::uint8_t) + 1];

	sprintf_s(hex_string, hex > 0xF ? "0x%x" : "0x0%x", hex);

	return std::string(hex_string);
}

std::uint8_t encrypt_byte(std::uint8_t byte)
{
	return byte ^ 0x41;
}

int main(int argument_count, char** argument_array)
{
	if (argument_count < 3)
	{
		printf("[+] usage: binary-dumper.exe binary_name.exe output_name");
		return -1;
	}

	std::vector<std::uint8_t>buffer{};
	util::open_binary_file(argument_array[1], buffer);

	std::uint16_t mz_sig = *reinterpret_cast<std::uint16_t*>(buffer.data());

	if (mz_sig != 0x5a4d)
	{
		printf("[+] invalid mz file\n");
		return -1;
	}

	printf("[+] mz [0x%x]\n", mz_sig);

	std::string normal_buffer_string = "std::uint8_t normal_buffer[] = {\n";
	std::string encrypted_buffer_string = "std::uint8_t encrypted_buffer[] = {\n";

	for (int i = 0; i < buffer.size(); i++)
	{
		std::uint8_t current_byte = buffer[i];
		std::uint8_t encrypted_current_byte = encrypt_byte(current_byte);

		if (i % 10 == 0 && i != 0)
		{
			normal_buffer_string += "\n\t";
			encrypted_buffer_string += "\n\t";
		}
		else if (i == 0)
		{
			normal_buffer_string += "\t";
			encrypted_buffer_string += "\t";
		}

		normal_buffer_string += hex_to_string(current_byte) + ", ";
		encrypted_buffer_string += hex_to_string(encrypted_current_byte) + ", ";
	}

	normal_buffer_string += "\n};\n";
	encrypted_buffer_string += "\n};\n";

	std::ofstream normal_file(std::string(argument_array[2]) + ".bin");
	normal_file << normal_buffer_string;
	normal_file.close();

	std::ofstream encrypted_file(std::string(argument_array[2]) + "-enc.bin");
	encrypted_file << encrypted_buffer_string;
	encrypted_file.close();

	return 0;
}
