// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define Kol_vo_bit (sizeof(TELEM) * 8)

TBitField::TBitField(int len)

{

if (len < 0)

throw"WRONG";

BitLen = len;

MemLen = (BitLen + Kol_vo_bit - 1)/Kol_vo_bit;

pMem = new TELEM[MemLen];

for (int i = 0; i < MemLen; i++)

pMem[i] = 0;

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования

{

BitLen = bf.BitLen;

MemLen = BitLen / Kol_vo_bit + 1;

pMem = new TELEM[MemLen];

for (int i = 0; i < MemLen; i++)

pMem[i] = bf.pMem[i];

}

TBitField::~TBitField()

{

delete[] pMem;

}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n

{

return n / Kol_vo_bit;

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n

{

return 1 << (n % Kol_vo_bit);

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)

{

return BitLen;

}

void TBitField::SetBit(const int n) // установить бит

{

if ((n < 0) || (n > BitLen))

throw "WRONG";

pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит

{

if ((n < 0) || (n > BitLen))

throw "WRONG";

pMem[GetMemIndex(n)] &= ~(GetMemMask(n));

}

int TBitField::GetBit(const int n) const // получить значение бита

{

if ((n < 0) || (n > BitLen))

throw "WRONG";

if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)

return 0;

else

return 1;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание

{

if (BitLen == bf.BitLen)

{

for (int i = 0; i < MemLen; i++)

pMem[i] = bf.pMem[i];

}

else

{

delete[] pMem;

BitLen = bf.BitLen;

MemLen = BitLen / Kol_vo_bit + 1;

pMem = new TELEM[MemLen];

for (int i = 0; i < MemLen; i++)

pMem[i] = bf.pMem[i];

}

return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение

{

if (BitLen != bf.BitLen)

return 0;

else

{

int flag = 1;

for (int i = 0; i < bf.MemLen; i++)

if (pMem[i] != bf.pMem[i])

flag = 0;

return flag;

}

}

int TBitField::operator!=(const TBitField &bf) const // сравнение

{

return !(*this == bf);

}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"

{

if (BitLen > bf.BitLen)

{

TBitField Res(BitLen);

for (int i = 0; i < bf.MemLen; i++)

{

Res.pMem[i]=pMem[i] | bf.pMem[i];

for (int i = bf.MemLen; i < Res.MemLen; i++)

Res.pMem[i] = pMem[i];

}

return Res;

}

else

{

TBitField Res(bf.BitLen);

for (int i = 0; i < MemLen; i++)

{

Res.pMem[i]=pMem[i] | bf.pMem[i];

for (int i = MemLen; i < Res.MemLen; i++)

Res.pMem[i] = bf.pMem[i];

}

return Res;

}

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"

{

if (BitLen > bf.BitLen)

{

TBitField Res(BitLen);

for (int i = 0; i < bf.MemLen; i++)

Res.pMem[i] = pMem[i] & bf.pMem[i];

for (int i = bf.MemLen; i < Res.MemLen; i++)

Res.pMem[i] = 0;

return Res;

}

else

{

TBitField Res(BitLen);

for (int i = 0; i < MemLen; i++)

Res.pMem[i] = pMem[i] & bf.pMem[i];

for (int i = bf.MemLen; i < Res.MemLen; i++)

Res.pMem[i] = 0;

return Res;

}

}

TBitField TBitField::operator~(void) // отрицание

{

TBitField Res(BitLen);

for (int i = 0; i < MemLen - 1; i++)

if (pMem[i]==0)

Res.pMem[i]=1;

else

Res.pMem[i]=0;

for (int i = ((MemLen - 1) * Kol_vo_bit); i < BitLen; i++)

if (GetBit(i) == 0)

Res.SetBit(i);

else

Res.ClrBit(i);

return Res;

}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод

{

cout << "Input BitLen :" << endl;

int len = 0;

istr >> len;

for (int i = 0; i < len; i++)

{

int a = 0;

istr >> a;

if (a == 1)

bf.SetBit(i);

}

return istr;

}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод

{

ostr << "{ ";

for (int i = 0; i < bf.BitLen; i++)

ostr << bf.GetBit(i);

ostr << "}\n";

return ostr;

}