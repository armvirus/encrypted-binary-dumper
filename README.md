# encrypted-binary-dumper
Takes a binary and dumps its opcodes to a file (encrypted binary (```-enc.bin```) extension / not encrypted (```.bin```) extension).
This project can be used to store binaries in a executable in a more stealthy way, which can't be found as easily as a non-encrypted buffer.

usage for decrypting the buffer for proper usage:
```ruby
std::uint8_t decrypt_byte(std::uint8_t byte)
{
	return byte ^ 0x41;
}

std::uint8_t encrypted_buffer_example[] =
{
	0x4a, 0x5d
};

void decrypt_buffer()
{
	for (int i = 0; i < sizeof(encrypted_buffer_example); i++)
	{
		encrypted_buffer_example[i] = decrypt_byte(encrypted_buffer_example[i]);
	}
}
```
I highly recommend changing the encrypt/decrypt byte function, you can use ^, +, -, rotate left (```rotl8```), rotate right (```rotr8```), and many more ways to encrypt bytes.
after you are done using the decrypted buffer you can safely zero it by using the winapi function ```ZeroMemory```
