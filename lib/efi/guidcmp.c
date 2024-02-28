#include <efi.h>




int32_t guidcmp(efi_guid_t *g1, efi_guid_t *g2) {
	int32_t *guid1 = (int32_t *)g1;
	int32_t *guid2 = (int32_t *)g2;
	int32_t ret = 0;

	ret = guid1[0] - guid2[0];
	ret |= guid1[1] - guid2[1];
	ret |= guid1[2] - guid2[2];
	ret |= guid1[3] - guid2[3];

	return ret;

}
