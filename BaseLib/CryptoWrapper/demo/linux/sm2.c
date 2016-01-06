#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "sm2.h"


#if 0
######################################
x86: CPU 2.8G
sm2_sign speed:147.058824/s
sm2_verify speed:116.414435/s
sm2_verify OK!===1
sm2_encrypt speed:74.404762/s
sm2_decrypt speed:150.602410/s
sm2_decrypt OK!

######################################

#endif


void my_ecc192_test()
{
	int pv_len;
	unsigned char pv[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF6,0x5A,0x8E,0xBA,0xA7,0x8D,0x49,0xFB,
 0xAA,0xB8,0x8C,0xCC,0x5D,0xC4,0x07,0x68,0xB4,0x0F,0x43,0x1C,0xE1,0x3B,0x2E,0xB6};
	int px_len;
	unsigned char px[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46,0x3D,0xED,0x0D,0xDA,0x97,0xF1,0x00,
 0x25,0x0C,0x85,0xE5,0x38,0x8C,0xAF,0xFE,0x9F,0x5F,0x74,0x73,0xD9,0x61,0x7F,0x75};
	int py_len;
	unsigned char py[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x85,0x85,0x00,0xD2,0xD1,0x0D,0xD8,
 0x1D,0x7E,0xE3,0x60,0xDC,0x47,0xD4,0x1D,0x22,0x5E,0x88,0x1D,0x6A,0x94,0x2D,0x80};
	int hash_len;
	unsigned char hash[] = {0x49,0x8C,0x74,0x88,0x3E,0x91,0xAA,0xEB,0xA7,0x1D,0x0D,0xA1,0xCB,0x6A,0x63,0x63,0x60,0xD1,0x70,0x06};
	int sign1_len;
	unsigned char sign1[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xBC,0xDE,0xB8,0x7F,0x6D,0x52,0x68,
 0x56,0xBD,0x50,0xA2,0xFC,0x6F,0x51,0x58,0xF1,0x12,0xD0,0x95,0x39,0x09,0xC9,0xFB};
	int sign2_len;
	unsigned char sign2[] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xEF,0xD8,0x60,0xC0,0xF3,0x76,0x09,
 0x35,0x63,0xC4,0xA1,0x68,0xF6,0x33,0xDC,0xBB,0x6D,0x33,0x4B,0x9F,0xD0,0xFD,0xD9};

	int i,j;

	printf("\n[my_ecc192_test_input]:");
	printf("\npv = ");
for(i=0; i<sizeof(pv); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",pv[i]);}
	printf("\npx = ");
for(i=0; i<sizeof(px); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",px[i]);}
	printf("\npy = ");
for(i=0; i<sizeof(py); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",py[i]);}
	printf("\nhash = ");
for(i=0; i<sizeof(hash); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",hash[i]);}
	printf("\nsign1 = ");
for(i=0; i<sizeof(sign1); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",sign1[i]);}
	printf("\nsign2 = ");
for(i=0; i<sizeof(sign2); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",sign2[i]);}

	printf("\n[priv_sign ]:");
	unsigned char cr[32],cs[32];
	int cr_len,cs_len;
	sm2_sign(hash,sizeof(hash),pv,sizeof(pv),cr,&cr_len,cs,&cs_len);
	printf("\ncr_len = %d cr = ",cr_len);
for(i=0; i<cr_len; i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",cr[i]);}
	printf("\ncs_len = %d cs = ",cs_len);
for(i=0; i<cs_len; i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",cs[i]);}

	printf("\n[verify sign ]: ");
	i = sm2_verify(hash,sizeof(hash),sign1,sizeof(sign1),sign2,sizeof(sign2),px,sizeof(px),py,sizeof(py));
	printf("%s\n",(i==0)?("err"):("ok"));

	
	printf("\n[my_test_sm2 ]:");
	printf("\nhash = ");
for(i=0; i<sizeof(hash); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",hash[i]);}
	memset(pv,0,sizeof(pv));
	memset(px,0,sizeof(px));
	memset(py,0,sizeof(py));

	printf("\nsm2_keygen_priv&pub...");
	sm2_keygen(px,&px_len,py,&py_len,pv,&pv_len);
	printf("\npv_len = %d pv = ",pv_len);
for(i=0; i<sizeof(pv); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",pv[i]);}
	printf("\npx_len = %d px = ",px_len);
for(i=0; i<sizeof(px); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",px[i]);}
	printf("\npy_len = %d py = ",py_len);
for(i=0; i<sizeof(py); i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",py[i]);}

	printf("\n[priv_sign ]:");
	sm2_sign(hash,sizeof(hash),pv,sizeof(pv),cr,&cr_len,cs,&cs_len);
	printf("\ncr_len = %d cr = ",cr_len);
for(i=0; i<cr_len; i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",cr[i]);}
	printf("\ncs_len = %d cs = ",cs_len);
for(i=0; i<cs_len; i++) {if(i%16 == 0)printf("\n");if(i%4 == 0)printf(" ");printf("%02x",cs[i]);}

	printf("\n[verify sign ]: ");
	i = sm2_verify(hash,sizeof(hash),cr,cr_len,cs,cs_len,px,sizeof(px),py,sizeof(py));
	printf("%s\n",(i==0)?("err"):("ok"));
}

void key_test()
{
        unsigned char ida[19] = "ALICE123@YAHOO.COM";
        unsigned char idb[18] = "BILL456@YAHOO.COM";
        unsigned char da[] = {0x6F,0xCB,0xA2,0xEF,0x9A,0xE0,0xAB,0x90,0x2B,0xC3,0xBD,0xE3,0xFF,0x91,0x5D,0x44,0xBA,0x4C,0xC7,0x8F,0x88,0xE2,0xF8,0xE7,0xF8,0x99,0x6D,0x3B,0x8C,0xCE,0xED,0xEE}; 
        unsigned char xa[] = {0x30,0x99,0x09,0x3B,0xF3,0xC1,0x37,0xD8,0xFC,0xBB,0xCD,0xF4,0xA2,0xAE,0x50,0xF3,0xB0,0xF2,0x16,0xC3,0x12,0x2D,0x79,0x42,0x5F,0xE0,0x3A,0x45,0xDB,0xFE,0x16,0x55};
        unsigned char ya[] = {0x3D,0xF7,0x9E,0x8D,0xAC,0x1C,0xF0,0xEC,0xBA,0xA2,0xF2,0xB4,0x9D,0x51,0xA4,0xB3,0x87,0xF2,0xEF,0xAF,0x48,0x23,0x39,0x08,0x6A,0x27,0xA8,0xE0,0x5B,0xAE,0xD9,0x8B};
        unsigned char db[] = {0x5E,0x35,0xD7,0xD3,0xF3,0xC5,0x4D,0xBA,0xC7,0x2E,0x61,0x81,0x9E,0x73,0x0B,0x01,0x9A,0x84,0x20,0x8C,0xA3,0xA3,0x5E,0x4C,0x2E,0x35,0x3D,0xFC,0xCB,0x2A,0x3B,0x53}; 
        unsigned char xb[] = {0x24,0x54,0x93,0xD4,0x46,0xC3,0x8D,0x8C,0xC0,0xF1,0x18,0x37,0x46,0x90,0xE7,0xDF,0x63,0x3A,0x8A,0x4B,0xFB,0x33,0x29,0xB5,0xEC,0xE6,0x04,0xB2,0xB4,0xF3,0x7F,0x43};
        unsigned char yb[] = {0x53,0xC0,0x86,0x9F,0x4B,0x9E,0x17,0x77,0x3D,0xE6,0x8F,0xEC,0x45,0xE1,0x49,0x04,0xE0,0xDE,0xA4,0x5B,0xF6,0xCE,0xCF,0x99,0x18,0xC8,0x5E,0xA0,0x47,0xC6,0x0A,0x4C};

        unsigned char kabuf[32], sa[32];
        unsigned char kbbuf[32], sb[32], s1[32], s2[32];
        unsigned char kx2[32], ky2[32];
        int kx2len, ky2len;
        unsigned char kx1[256], ky1[256], ra[256], xv[32], yv[32];
        int kx1len,ky1len, ralen, xvlen, yvlen;

#if SM2_DEBUG
#else
        sm2_keygen(xa, &kx1len, ya, &ky1len, da, &ralen);
        sm2_keygen(xb, &kx1len, yb, &ky1len, db, &ralen);
#endif

        sm2_keyagreement_a1_3(kx1, &kx1len, ky1, &ky1len, ra, &ralen);

        sm2_keyagreement_b1_9(
                                                  kx1, kx1len,
                                                  ky1, ky1len,
                                                  xa, 32,
                                                  ya, 32,
                                                  db, 32,
                                                  xb, 32,
                                                  yb, 32,
                                                  ida, 18,
                                                  idb, 17,
                                                  16,
                                                  kbbuf,
                                                  kx2, &kx2len,
                                                  ky2, &ky2len,
                                                  xv, &xvlen,
                                                  yv, &yvlen,
                                                  sb
                                                  );


        sm2_keyagreement_a4_10(
                                                  kx1, kx1len,
                                                  ky1, ky1len,
                                                  xa, 32,
                                                  ya, 32,
                                                  da, 32,
                                                  xb, 32,
                                                  yb, 32,
                                                  ida, 18,
                                                  idb, 17,
                                                  kx2, kx2len,
                                                  ky2, ky2len,
                                                  ra, ralen,
                                                  16,
                                                  kabuf,
                                                  s1,
                                                  sa
                                                  );

        sm2_keyagreement_b10(
                                                  xa, 32,
                                                  ya, 32,
                                                  xb, 32,
                                                  yb, 32,
                                                  kx1, 32,
                                                  ky1, 32,
                                                  kx2, 32,
                                                  ky2, 32,
                                                  xv, xvlen,
                                                  yv, yvlen,
                                                  ida, 18,
                                                  idb, 17,
                                                  s2
                );

        if(memcmp(s1, sb, 32) != 0)
        {
                printf("key_test error ! \n");
                return;
        }
        if(memcmp(kabuf, kbbuf, 16) != 0)
        {
                printf("key_test error ! \n");
                return;
        }

        if(memcmp(s2, sa, 32) != 0)
        {
                printf("key_test error ! \n");
                return;
        }

        printf("key_test OK ! \n");


}
#if 0
int main()
{
	int rlen, slen, rv;
/*
	unsigned char digest_sm2[] = {0xB5,0x24,0xF5,0x52,0xCD,0x82,0xB8,0xB0,0x28,0x47,0x6E,0x00,0x5C,0x37,0x7F,0xB1,0x9A,0x87,0xE6,0xFC,0x68,0x2D,0x48,0xBB,0x5D,0x42,0xE3,0xD9,0xB9,0xEF,0xFE,0x76};
	unsigned char kA_sm2[] = {0x12,0x8B,0x2F,0xA8,0xBD,0x43,0x3C,0x6C,0x06,0x8C,0x8D,0x80,0x3D,0xFF,0x79,0x79,0x2A,0x51,0x9A,0x55,0x17,0x1B,0x1B,0x65,0x0C,0x23,0x66,0x1D,0x15,0x89,0x72,0x63}; 
	unsigned char kAx_sm2[] = {0x0A,0xE4,0xC7,0x79,0x8A,0xA0,0xF1,0x19,0x47,0x1B,0xEE,0x11,0x82,0x5B,0xE4,0x62,0x02,0xBB,0x79,0xE2,0xA5,0x84,0x44,0x95,0xE9,0x7C,0x04,0xFF,0x4D,0xF2,0x54,0x8A};
	unsigned char kAy_sm2[] = {0x7C,0x02,0x40,0xF8,0x8F,0x1C,0xD4,0xE1,0x63,0x52,0xA7,0x3C,0x17,0xB7,0xF1,0x6F,0x07,0x35,0x3E,0x53,0xA1,0x76,0xD6,0x84,0xA9,0xFE,0x0C,0x6B,0xB7,0x98,0xE8,0x57};
	unsigned char r_sm2[] = {0x40,0xF1,0xEC,0x59,0xF7,0x93,0xD9,0xF4,0x9E,0x09,0xDC,0xEF,0x49,0x13,0x0D,0x41,0x94,0xF7,0x9F,0xB1,0xEE,0xD2,0xCA,0xA5,0x5B,0xAC,0xDB,0x49,0xC4,0xE7,0x55,0xD1};
	unsigned char s_sm2[] = {0x6F,0xC6,0xDA,0xC3,0x2C,0x5D,0x5C,0xF1,0x0C,0x77,0xDF,0xB2,0x0F,0x7C,0x2E,0xB6,0x67,0xA4,0x57,0x87,0x2F,0xB0,0x9E,0xC5,0x63,0x27,0xA6,0x7E,0xC7,0xDE,0xEB,0xE7};
	
	
	unsigned char dB[] = {0x16,0x49,0xAB,0x77,0xA0,0x06,0x37,0xBD,0x5E,0x2E,0xFE,0x28,0x3F,0xBF,0x35,0x35,0x34,0xAA,0x7F,0x7C,0xB8,0x94,0x63,0xF2,0x08,0xDD,0xBC,0x29,0x20,0xBB,0x0D,0xA0}; 
	unsigned char xB[] = {0x43,0x5B,0x39,0xCC,0xA8,0xF3,0xB5,0x08,0xC1,0x48,0x8A,0xFC,0x67,0xBE,0x49,0x1A,0x0F,0x7B,0xA0,0x7E,0x58,0x1A,0x0E,0x48,0x49,0xA5,0xCF,0x70,0x62,0x8A,0x7E,0x0A};
	unsigned char yB[] = {0x75,0xDD,0xBA,0x78,0xF1,0x5F,0xEE,0xCB,0x4C,0x78,0x95,0xE2,0xC1,0xCD,0xF5,0xFE,0x01,0xDE,0xBB,0x2C,0xDB,0xAD,0xF4,0x53,0x99,0xCC,0xF7,0x7B,0xBA,0x07,0x6A,0x42};
	unsigned char tx[] = "encryption standard";
*/

	unsigned char digest_sm2[] = {0x38,0x54,0xC4,0x63,0xFA,0x3F,0x73,0x78,0x36,0x21,0xB1,0xCE,0x4E,0xF8,0x3F,0x7C,0x78,0x04,0x8A,0xAC,0x79,0xB2,0x21,0xFC,0xDD,0x29,0x08,0x66,0xCC,0x13,0x11,0x74};
	unsigned char kA_sm2[] = {0xC2,0x42,0x93,0x9D,0xDA,0xB6,0xFC,0xC0,0x7B,0x66,0x76,0xC0,0x7D,0x2D,0xC1,0x17,0xEC,0x68,0xA0,0x91,0x42,0xC2,0x5C,0x00,0x86,0x30,0xB9,0x75,0x67,0x86,0x16,0x2D}; 
	unsigned char kAx_sm2[] = {0x5C,0xA4,0xE4,0x40,0xC5,0x08,0xC4,0x5F,0xE7,0xD7,0x58,0xAB,0x10,0xC4,0x5D,0x82,0x37,0xC4,0xF9,0x55,0x9F,0x7D,0x46,0x61,0x85,0xF2,0x95,0x39,0x9F,0x0A,0xA3,0x7D};
	unsigned char kAy_sm2[] = {0x59,0xAD,0x8A,0x3C,0xD1,0x79,0x03,0x28,0x76,0x81,0xBF,0x9D,0x21,0xDA,0x2E,0xB3,0x16,0xA0,0xCE,0x8F,0xD4,0x1C,0x89,0xCE,0x1E,0x2B,0x3F,0x1B,0x8E,0x04,0x1A,0xBA};
	unsigned char r_sm2[] = {0x6E,0x5D,0xB4,0x9D,0xBD,0x09,0x92,0xB9,0x70,0x40,0x08,0x0A,0x96,0x00,0x3C,0x72,0x1C,0xDB,0x9C,0xF6,0x4C,0x88,0xD7,0x43,0x21,0xFC,0x2F,0x63,0x0A,0xDF,0x37,0x74};
	unsigned char s_sm2[] = {0x2F,0x6D,0xFF,0x45,0x3D,0xFC,0x8D,0x7A,0x50,0x6D,0x3F,0x52,0x30,0x1B,0xEE,0x52,0x9E,0x62,0xFD,0xDD,0x38,0x94,0x8F,0x0D,0x5D,0x2C,0xBC,0xBC,0x55,0x90,0x0C,0xFA};
	
	unsigned char dB[] = {0x9E,0xD4,0x5E,0x25,0x82,0x6B,0x67,0xE8,0xAC,0xCD,0x63,0xD3,0xE1,0x60,0x51,0x79,0xCF,0x41,0x7E,0x2A,0xDB,0x39,0x13,0x61,0xCD,0xBF,0x36,0x7E,0xC1,0x68,0x7E,0xCE}; 
	unsigned char xB[] = {0xF6,0xD3,0x26,0x50,0x9B,0xA8,0xDA,0x09,0xAA,0x34,0xCD,0x85,0xAE,0xF7,0x9D,0xBA,0x45,0xFD,0x17,0xE6,0x75,0x54,0x1B,0x15,0xEF,0x5E,0xC9,0xB8,0xF4,0xAB,0x18,0xBC};
	unsigned char yB[] = {0xA1,0x3A,0x2F,0x04,0xC6,0xBC,0x16,0x07,0xCA,0x72,0xCC,0x29,0x6A,0x9A,0xCF,0x7B,0xF2,0x68,0x91,0xC3,0x2B,0x21,0x0B,0x94,0x7C,0xA8,0x8F,0x3B,0x92,0x80,0x1E,0x8F};
	unsigned char tx[] = "encryption standard";
	unsigned char etx[256] ;
	unsigned char mtx[256] ;
	
	clock_t start,end;
	double tt;
	int j;

//	unsigned char userid[] = "ALICE123@YAHOO.COM";
//	unsigned char msg[] = "message digest";

//	key_test();
	int loop = 200;
	int wxlen, wylen, privkeylen;

//	sm2_keygen(kAx_sm2, &wxlen, kAy_sm2, &wylen, kA_sm2, &privkeylen);
//	sm2_keygen(xB, &wxlen, yB, &wylen, dB, &privkeylen);


	start = clock();

	for(j=0;j<loop;j++)
		sm2_sign(digest_sm2,32,kA_sm2,32,r_sm2,&rlen,s_sm2,&slen);

	end = clock();

	tt = (double)(end-start)/CLOCKS_PER_SEC;
	printf("sm2_sign speed:%lf/s\n", (double)j/tt);

	start = clock();

	for(j=0;j<loop;j++)
		rv = sm2_verify(digest_sm2,32,r_sm2,32,s_sm2,32,kAx_sm2,32,kAy_sm2,32);

	end = clock();
	tt = (double)(end-start)/CLOCKS_PER_SEC;
	printf("sm2_verify speed:%lf/s\n", (double)j/tt);

	if(rv != 1) 
		printf("sm2_verify error!===%d\n",rv);
	else
		printf("sm2_verify OK!===%d\n",rv);
	
	
	start = clock();

	for(j=0;j<loop;j++)
		sm2_encrypt(tx,19,xB,32,yB,32,etx);

	end = clock();
	tt = (double)(end-start)/CLOCKS_PER_SEC;
	printf("sm2_encrypt speed:%lf/s\n", (double)j/tt);



	start = clock();
	for(j=0;j<loop;j++)
		sm2_decrypt(etx,64+19+32,dB,32,mtx);
	end = clock();
	tt = (double)(end-start)/CLOCKS_PER_SEC;
	printf("sm2_decrypt speed:%lf/s\n", (double)j/tt);

	if(sm2_decrypt(etx,64+19+32,dB,32,mtx) < 0)
		printf("sm2_decrypt error!\n");
	else
		printf("sm2_decrypt OK!\n");
	

//	my_ecc192_test();
	return 0;

}

#endif

void PrintBuf(unsigned char *buf, int	buflen) 
{
	int i;
	printf("\n");
	printf("len = %d\n", buflen);
	for(i=0; i<buflen; i++) {
		if (i % 32 != 31)
			printf("%02x", buf[i]);
		else
			printf("%02x\n", buf[i]);
	}
	printf("\n");
	return;
}

int main()
{
#if 0
	u_char pubKey_x[32],pubKey_y[32];
	u_char privkey[32];
	int pubKey_x_len,pubKey_y_len,privkeylen;
	int i;
	//生成SM2公私钥对
	sm2_keygen(pubKey_x,&pubKey_x_len,pubKey_y,&pubKey_y_len,privkey,&privkeylen);
/**/
	printf("pubKey_x = ");
	for(i=0;i<32;i++)
	{
		printf("%02x",pubKey_x[i]);
	}
	printf("\npubKey_x_len = %d \n",pubKey_x_len);
    printf("***************************************************\n");

	printf("pubKey_y = ");
	for(i=0;i<32;i++)
	{
		printf("%02x",pubKey_y[i]);
	}
	printf("\npubKey_y_len = %d \n",pubKey_y_len);
	printf("***************************************************\n");

	printf("privkey = ");
	for(i=0;i<32;i++)
	{
		printf("%02x",privkey[i]);
	}
	printf("\nprivkeylen = %d \n",privkeylen);

	
	u_char hash[32];
	u_char userid[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	u_char data[]={"1234567812345678"};
	uchar  sign_r[32]={};
	int    sign_r_len;
	uchar  sign_s[32]={};
	int    sign_s_len;
	int ret = sm3_e(userid,8,pubKey_x,32,pubKey_y,32,data,strlen((char *)data), hash);
	printf("ret = %d \n",ret);

	sm2_sign(hash,32, privkey,32, sign_r, &sign_r_len, sign_s, &sign_s_len);
	
	ret = sm2_verify(hash,32, sign_r, 32, sign_s,32, pubKey_x, 32, pubKey_y, 32);
	printf("ret = %d \n",ret);
#endif
	u_char pubKey_x[32],pubKey_y[32];
	u_char privkey[32];
	int pubKey_x_len,pubKey_y_len,privkeylen;
	int i;

	sm2_keygen(pubKey_x,&pubKey_x_len,pubKey_y,&pubKey_y_len,privkey,&privkeylen);

	printf("pubKey_x = ");
	for(i=0;i<32;i++)
	{
		printf("%02x",pubKey_x[i]);
	}
	printf("\npubKey_x_len = %d \n",pubKey_x_len);
    printf("***************************************************\n");

	printf("pubKey_y = ");
	for(i=0;i<32;i++)
	{
		printf("%02x",pubKey_y[i]);
	}
	printf("\npubKey_y_len = %d \n",pubKey_y_len);
	printf("***************************************************\n");

	printf("privkey = ");
	for(i=0;i<32;i++)
	{
		printf("%02x",privkey[i]);
	}
	printf("\nprivkeylen = %d \n",privkeylen);

	unsigned char tx[] = "encryption standard";
	unsigned char etx[256] ;
	unsigned char mtx[256] ;
	
	
	printf("src = %s\n", tx);

	memset(etx, 0, 256);
	memset(mtx, 0, 256);
	sm2_encrypt(tx,19,pubKey_x,32,pubKey_y,32,etx);

	printf("Encrypted: ");
	PrintBuf(etx, 64+19+32);


	if(sm2_decrypt(etx,64+19+32,privkey,32,mtx) < 0)
	{
			printf("sm2_decrypt error!\n");
	}
	else
			printf("sm2_decrypt OK!\n");


	printf("des = %s", mtx);
	
	PrintBuf(mtx, 19);
	return 0;
}




