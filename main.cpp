#include "menu.h"

int main() {
    MLL daftarLapangan;
    Queue antrean;

    // bikin list dan queue kosong
    createMLL(daftarLapangan);
    createQueue(antrean);

    // muat data
    muatData(daftarLapangan, antrean);

    // jalankan menu utama
    menuUtama(daftarLapangan, antrean);

    // simpan data
    simpanData(daftarLapangan, antrean);

    return 0;
}