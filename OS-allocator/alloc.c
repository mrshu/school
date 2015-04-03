#include "wrapper.h"

/* Kod funkcii my_alloc a my_free nahradte vlastnym. Nepouzivajte ziadne
 * globalne ani staticke premenne; jedina globalna pamat je dostupna pomocou
 * mread/mwrite/msize, ktorych popis najdete vo wrapper.h */


/*functions to use
  unsigned int msize(void);
  uint8_t mread(unsigned int addr);
  void mwrite(unsigned int addr, uint8_t val);
 */


struct block_info{
  unsigned int next_addr;
  unsigned int addr_end;
}

block_info  read_info(unsigned int addr){
  
    uint8_t n1 = mread(addr);
    uint8_t n2 = mread(addr+1);
    uint8_t n3 = mread(addr+2);
    uint8_t n4 = mread(addr+3);
  
    uint8_t e1 = mread(addr+4);
    uint8_t e2 = mread(addr+5);
    uint8_t e3 = mread(addr+6);
    uint8_t e4 = mread(addr+7);
  
    struct block_info readed;
    readed.next_addr= n1;
    readed.next_addr = readed.next_addr<<8;
    readed.next_addr += n2;
    readed.next_addr = readed.next_addr<<8;
    readed.next_addr += n3;
    readed.next_addr = readed.next_addr<<8;
    readed.next_addr += n4;
  
    readed.addr_end = e1;
    readed.addr_end = readed.addr_end<<8;
    readed.addr_end += e2;
    readed.addr_end = readed.addr_end<<8;
    readed.addr_end += e3;
    readed.addr_end = readed.addr_end<<8;
    readed.addr_end += e4;
  
  return readed;
}

void write_info(unsigned int addr, block_info towrite){
    
    uint8_t n4 = block_info.next_addr % (1<<8);
    block_info.next_addr  = block_info.next_addr>>8;
    uint8_t n3 = block_info.next_addr  % (1<<8);
    block_info.next_addr  = block_info.next_addr >>8;
    uint8_t n2 = block_info.next_addr  % (1<<8);
    block_info.next_addr  = block_info.next_addr >>8;
    uint8_t n1  = block_info.next_addr  % (1<<8);
  
    uint8_t e4 = block_info.addr_end % (1<<8);
    block_info.addr_end  = block_info.addr_end>>8;
    uint8_t e3 = block_info.addr_end  % (1<<8);
    block_info.addr_end  = block_info.addr_end >>8;
    uint8_t e2 = block_info.addr_end % (1<<8);
    block_info.addr_end  = block_info.addr_end >>8;
    uint8_t e1  = block_info.addr_end  % (1<<8);
  
    
    mwrite( addr , b1 );
    mwrite( addr+1 , b2 );
    mwrite( addr+2 , b3 );
    mwrite( addr+3 , b4 );
    
    mwrite( addr+4 , e1 );
    mwrite( addr+5 , e2 );
    mwrite( addr+6 , e3 );
    mwrite( addr+7 , e4 );
}




/**
 * Inicializacia pamate
 *
 * Zavola sa, v stave, ked sa zacina s prazdnou pamatou, ktora je inicializovana
 * na 0.
 */
void my_init(void) {
	//split 32-bit int 4 bytes 
	unsigned int total_size = msize();
	uint8_t size_part_4 = total_size % (1<<8);
	total_size = total_size>>8;
	uint8_t size_part_3 = total_size % (1<<8);
	total_size = total_size>>8;
	uint8_t size_part_2 = total_size % (1<<8);
	total_size = total_size>>8;
	uint8_t size_part_1 = total_size % (1<<8);
	// 0..3 bytes -> total memory
	mwrite(0,size_part_1);
	mwrite(1,size_part_2);
	mwrite(2,size_part_3);
	mwrite(3,size_part_4);

	return;
}



/**
 * Poziadavka na alokaciu 'size' pamate. 
 *
 * Ak sa pamat podari alokovat, navratova hodnota je adresou prveho bajtu
 * alokovaneho priestoru v RAM. Pokial pamat uz nie je mozne alokovat, funkcia
 * vracia FAIL.
 */
int my_alloc(unsigned int size) {
	
	return 1;
}

/**
 * Poziadavka na uvolnenie alokovanej pamate na adrese 'addr'.
 *
 * Ak bola pamat zacinajuca na adrese 'addr' alokovana, my_free ju uvolni a
 * vrati OK. Ak je adresa 'addr' chybna (nezacina na nej ziadna alokovana
 * pamat), my_free vracia FAIL.
 */

int my_free(unsigned int addr) {


	return OK;
}
