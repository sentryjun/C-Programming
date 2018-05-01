#pragma pack(1)

#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef long LONG;
class head {
public:
	WORD type;
	DWORD size;
	WORD v1;
	WORD v2;
	DWORD bits;
};
class info {
public:
	DWORD infoSize;
	LONG Width;
	LONG HEIGHT;
	WORD planes;
	WORD BitCount;
	DWORD Compression;
	DWORD BMPSize;
	LONG XPerM;
	LONG YPerM;
	DWORD ColorUsed;
	DWORD ColorImport;
};
class RGB {
public:
	RGB() :blue(0), green(0), red(0) {}
	BYTE blue;
	BYTE green;
	BYTE red;
};
int getDiff(info & inf) {
	int SizePerLine = (inf.Width * inf.BitCount + 31) / 8;
	SizePerLine -= (SizePerLine % 4);
	return SizePerLine - inf.Width * inf.BitCount / 8;
}
void trans(ifstream & src, ofstream& dest, head& ohead, info & inf) {
	head nhead = ohead;
	info ninf = inf;
	ninf.HEIGHT = inf.Width;
	ninf.Width = inf.HEIGHT;
	int diff = getDiff(inf);
	RGB * pic = new RGB[inf.HEIGHT * inf.Width];
	for (int i = 0; i < inf.HEIGHT; i++) {
		src.read((char*)(pic + inf.Width*i), sizeof(RGB)*inf.Width);
		src.seekg(diff, ios::cur);
	}
	diff = getDiff(ninf);
	char* zero = new char[diff + 1];
	memset(zero, 0, diff + 1);
	ninf.BMPSize = ninf.HEIGHT*(ninf.Width + diff);
	nhead.size = ninf.BMPSize + sizeof(ninf) + sizeof(nhead);
	RGB * npic = new RGB[ninf.HEIGHT * ninf.Width];
	for (int i = 0; i < ninf.HEIGHT; i++) {
		for (int j = 0; j < ninf.Width; j++) {
			*(npic + ninf.Width*(ninf.HEIGHT - 1 - i) + j) = *(pic + j*inf.Width + i);
		}
	}
	dest.write((char*)&nhead, sizeof(head));
	dest.write((char*)&ninf, sizeof(info));
	for (int i = 0; i < ninf.HEIGHT; i++) {
		dest.write((char*)(npic + ninf.Width*i), ninf.Width * sizeof(RGB));
		dest.write((char*)zero, diff);
	}

}
int main(int argc, char**argv) {
	char* src;
	char* dest;
    if (argc != 3) {
        cout << "usage: rotatebmp [srcfile_path] [destfile_path]\n";
        return 0;
    }
	src = argv[1];
	dest = argv[2];
	head fheader;
	info inf;
	ifstream in(src, ios::in | ios::binary);
	ofstream out(dest, ios::out | ios::binary);
	in.read((char*)&fheader, sizeof(head));
	in.read((char*)&inf, sizeof(info));
	trans(in, out, fheader, inf);
	return 0;
}