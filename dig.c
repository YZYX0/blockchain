#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "Dig.h"
void struct2str(BLOCK *p, BYTE *s)
{
	int i;
	for (i = 0; i < blockBytes; i++)
		s[i] = *((BYTE *)p + i);
	s[i] = "\0";   
}
void long2str(long long n, BYTE *s)  
{
	int i;
	long long a = n;
	for (i = 0; i < 8; i++)
		s[i] = *((BYTE *)&a + i);
}
void Block_init(BLOCK *p)
{
	int i;
	p->chain_version = 101;
	memset(p->prev_hash, 0, sizeof(BYTE) * 32);
	p->nonce1 = 0;
	p->nonce2 = 0;
	for (i = 0; i < 32; i++)
		p->coinbase[i] = rand() % 256;//0-255����� 
	p->award = 100;

}
int Dig(SHA256_CTX *ctx, BLOCK *p, BYTE *hash, int n0)
//ͨ��nonce1 nonce2���ϼ�1���ҵ�nonce1 nonce2 ʹ��block��hash���㿪ͷ��n0��16����0������test������֤��

{
	long long i, j;
	int v;
	int k;
	BYTE str[blockBytes + 1];//�Կ��ַ���β ����+1 
	struct2str(p, str);
	v = test(ctx, str, hash, n0);

	for (i = 0; v == 0 && i < MaxNum; i++)
	{
		long2str(i, &str[40]);//ֱ���޸��ַ������ڵ�ֵ����������struct2str ���Ч�� 
		for (j = 0; v == 0 && j < MaxNum; j++)
		{
			long2str(j, &str[48]);
			v = test(ctx, str, hash, n0);
		}
		if (v)//����Ҫ��
		{
			p->nonce1 = i;
			p->nonce2 = j;
			
			//for (k = 0; k < 96; k++)
				//printf("%d ", str[k]);
			//printf("\n");//��֤�ַ�������
			printf("nonce1:%lld nonce2:%lld\n", i, j);//ע��lld������ȷ��ʾlong long  
			return 1;
		}
	}
	return 0;
}
int test(SHA256_CTX *ctx, BYTE *str, BYTE *hash, int n)
// �ַ�������str ʹ��hashǰn��16������Ϊ0 ���㷵��1 
{
	int i;
	sha256_update(ctx, str, strlen(str));
	sha256_final(ctx, hash);
	if (n % 2 == 0)//nΪż��
	{
		
		i = 0;
		while (i < n / 2)
			if (hash[i++] != 0)
			{
				return(0);
			}
		return(1);
	}
	else//nΪ���� 
	{
		
		i = 0;
		while (i < (n-1) / 2)
			if (hash[i++] != 0)
			{
				return(0);
			}
		if (hash[i] <= 0x0f)//��n��ʮ������λΪ0
			return(1);
		else
			return(0);
	}

}