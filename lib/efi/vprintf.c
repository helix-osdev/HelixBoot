#include <efi.h>
#include <elf/elf.h>
#include <devices/uart.h>






efi_status_t vprintf(char16_t *fmt, va_list args) {
	efi_status_t ret = 0;
	char16_t buf[1024];


	while(*fmt != '\0') {
		if (*fmt == '%') {
			fmt++;

			switch(*fmt) {
				case 'c':
					buf[0] = va_arg(args, int);
					buf[1] = '\0';

					uart_puts(buf);
					fmt++;
					break;

				case 's':
					char16_t *s = va_arg(args, char16_t*);
					uart_puts(s);
					
					fmt++;
					break;

				case 'i':
				case 'd':
					int32_t n = va_arg(args, int32_t);
					
					itoa(n, buf, 10);
					uart_puts(buf);

					fmt++;
					break;

				case 'u':
					uint64_t n2 = va_arg(args, uint64_t);

					itoa(n2, buf, 10);
					uart_puts(buf);

					fmt++;
					break;

				case 'b':
					uint64_t n3 = va_arg(args, uint64_t);

					itoa(n3, buf, 2);
					uart_puts(buf);

					fmt++;
					break;

				case 'o':
					uint64_t n4 = va_arg(args, uint64_t);

					itoa(n4, buf, 8);
					uart_puts(buf);

					fmt++;
					break;

				case 'x':
				case 'X':
					uint64_t n5 = va_arg(args, uint64_t);

					itoa(n5, buf, 16);
					uart_puts(buf);

					fmt++;
					break;

				case 'e':
					uint64_t elf_err = va_arg(args, uint64_t);
					
					switch(elf_err) {
						case ET_NONE:
							strcpy(buf, L"None");
							break;

						case ET_EXEC:
							strcpy(buf, L"Executable");
							break;

						case ET_DYN:
							strcpy(buf, L"Dynamic");
							break;

						case ET_REL:
							strcpy(buf, L"Relocatable");
							break;
						
						default:
							strcpy(buf, L"Unknown");
							break;
					}

					uart_puts(buf);
					fmt++;
					break;

				case 'r':
					uint64_t err = va_arg(args, uint64_t);

					switch(err) {
						case EFI_LOAD_ERROR:
							strcpy(buf, L"Load Error");
							break;

						case EFI_INVALID_PARAMETER:
							strcpy(buf, L"Invalid Parameter");
							break;

						case EFI_UNSUPPORTED:
							strcpy(buf, L"Unsupported");
							break;

						case EFI_BAD_BUFFER_SIZE:
							strcpy(buf, L"Bad Buffer Size");
							break;

						case EFI_BUFFER_TOO_SMALL:
							strcpy(buf, L"Buffer Too Small");
							break;

						case EFI_DEVICE_NOT_READY:
							strcpy(buf, L"Device not ready");
							break;

						case EFI_DEVICE_ERROR:
							strcpy(buf, L"Device Error");
							break;

						case EFI_WRITE_PROTECTED:
							strcpy(buf, L"Write Protected");
							break;

						case EFI_OUT_OF_RESOURCES:
							strcpy(buf, L"Out of resources");
							break;

						case EFI_VOLUME_CORRUPTED:
							strcpy(buf, L"Volume Corrupted");
							break;

						case EFI_VOLUME_FULL:
							strcpy(buf, L"Volume Full");
							break;

						case EFI_NO_MEDIA:
							strcpy(buf, L"No Media");
							break;

						case EFI_MEDIA_CHANGED:
							strcpy(buf, L"Media Changed");
							break;

						case EFI_NOT_FOUND:
							strcpy(buf, L"Not Found");
							break;

						case EFI_ACCESS_DENIED:
							strcpy(buf, L"Access Denied");
							break;

						case EFI_NO_RESPONSE:
							strcpy(buf, L"No Response");
							break;

						case EFI_NO_MAPPING:
							strcpy(buf, L"No Mapping");
							break;

						case EFI_TIMEOUT:
							strcpy(buf, L"Timout");
							break;

						case EFI_NOT_STARTED:
							strcpy(buf, L"Not Started");
							break;

						case EFI_ALREADY_STARTED:
							strcpy(buf, L"Already Started");
							break;

						case EFI_ABORTED:
							strcpy(buf, L"Aborted");
							break;

						case EFI_ICMP_ERROR:
							strcpy(buf, L"ICMP Error");
							break;

						case EFI_TFTP_ERROR:
							strcpy(buf, L"TFTP Error");
							break;

						case EFI_PROTOCOL_ERROR:
							strcpy(buf, L"Protocol Error");
							break;

						case EFI_INCOMPATIBLE_VERSION:
							strcpy(buf, L"Incompatible Version");
							break;

						case EFI_SECURITY_VIOLATION:
							strcpy(buf, L"Security Violation");
							break;

						case EFI_CRC_ERROR:
							strcpy(buf, L"CRC Error");
							break;

						case EFI_END_OF_MEDIA:
							strcpy(buf, L"End of Media");
							break;

						case EFI_END_OF_FILE:
							strcpy(buf, L"End of File");
							break;

						case EFI_INVALID_LANGUAGE:
							strcpy(buf, L"Invalid Language");
							break;

						case EFI_COMPROMISED_DATA:
							strcpy(buf, L"Compromised Data");
							break;

						case EFI_IP_ADDRESS_CONFLICT:
							strcpy(buf, L"IP Conflict");
							break;

						case EFI_HTTP_ERROR:
							strcpy(buf, L"HTTP Error");
							break;

						default:
							strcpy(buf, L"Success");
							break;
					}

					uart_puts(buf);
					fmt++;
					break;

				default:
					fmt++;
					break;
			}
		}

		buf[0] = *fmt;
		buf[1] = '\0';

		uart_puts(buf);
		fmt++;
	}

	return EFI_SUCCESS;
}
