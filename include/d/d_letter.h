#ifndef D_LETTER_H
#define D_LETTER_H

bool dLetter_isNoSend(u16);
void dLetter_send(u16);
bool dLetter_isSend(u16);
bool dLetter_stock(u16);
bool dLetter_isStock(u16);
void dLetter_read(u16);
bool dLetter_isRead(u16);
void dLetter_delivery(u16);
void dLetter_autoStock(u16);
bool dLetter_isDelivery(u16);

#endif /* D_LETTER_H */
