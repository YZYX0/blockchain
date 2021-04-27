#pragma once
#ifndef mining_h
#define mining_h

#include "sha256.h"
#define blockBytes 96 //每个区块所占字节数 
#define N0 3  //hash开头有N0个16进制0 
#define MaxNum 1000000 //nonce1,nonce2的最大数 

typedef struct {
	long long chain_version;//8 byte
	BYTE prev_hash[32];//32 byte
	long long nonce1;//8 byte
	long long nonce2;//8 byte
	BYTE coinbase[32];//32 byte 
	double award;//8 byte  
} BLOCK;

void Block_init(BLOCK *p);
int Dig(SHA256_CTX *ctx, BLOCK *p, BYTE *hash, int n0);
//找到nonce1 nonce2 使得block的hash满足开头有n0个16进制0 
#endif  
