#include "main.h"

ColaCircular::ColaCircular(uint32_t capacidad)
	: m_tam(capacidad ? capacidad : 1), 
	m_inxIn(0), m_inxOut(0) {
    m_buf = new uint8_t[m_tam];   
}

ColaCircular::~ColaCircular() {
    delete[] m_buf;
    m_buf   = 0;
    m_tam   = 0;
    m_inxIn = 0;
    m_inxOut= 0;
}

uint8_t ColaCircular::push(uint8_t dato) 
{
    m_buf[m_inxIn] = dato;
    m_inxIn++;
    m_inxIn %= m_tam;
    return 1;
}

uint8_t ColaCircular::pop(uint8_t& dato) 
{
    if (m_inxIn == m_inxOut) 
		return 0;
    dato = m_buf[m_inxOut];
    m_inxOut++;
    m_inxOut %= m_tam;
    return 1;
}
