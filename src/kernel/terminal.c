#include "terminal.h"

static terminal_t gTerminal;

uint32_t _term_maxCharRow(terminal_t* const pTerm) {
  return ((pTerm->screenSize[0] / TERMINAL_FONT_SIZE_X > TERMINAL_MAX_WIDTH) ? TERMINAL_MAX_WIDTH : (pTerm->screenSize[0] / TERMINAL_FONT_SIZE_X));
}

uint32_t _term_maxCharCol(terminal_t* const pTerm) {
  return ((pTerm->screenSize[1] / TERMINAL_FONT_SIZE_Y > TERMINAL_MAX_HEIGHT) ? TERMINAL_MAX_HEIGHT : (pTerm->screenSize[1] / TERMINAL_FONT_SIZE_Y));
}

void term_init(terminal_t *const pTerm, PFN_terminalScreenSetPixel setPixelFn, PFN_terminalScreenDrawFunction drawFn, const uint32_t screenWidth, const uint32_t screenHeight) {
  pTerm->draw = drawFn;
  pTerm->setPixel = setPixelFn;
  pTerm->screenSize[0] = screenWidth;
  pTerm->screenSize[1] = screenHeight;
}

void term_clear(terminal_t *const pTerm) {
  pTerm->cursorPosition = 0;
  memset(pTerm->textBuffer, 0, TERMINAL_MAX_WIDTH * TERMINAL_MAX_HEIGHT);
}

void term_setCursor(terminal_t* const pTerm, uint32_t x, uint32_t y) {
  pTerm->cursorPosition = y * _term_maxCharRow(pTerm) + x;
}

void term_print(terminal_t *const pTerm, const char *text) {
  /* Ste temp text buffer*/
  char temp[TERMINAL_MAX_WIDTH * TERMINAL_MAX_HEIGHT] = {};
  /* Copy data to temp text buffer */
  memcpy(temp, pTerm->textBuffer, _term_maxCharCol(pTerm) * _term_maxCharRow(pTerm));
  /* Clear main text buffer */
  term_clear(pTerm);
  /* Copy temp text buffer to main text buffer at offset strlen(text) */
  memcpy(pTerm->textBuffer + strlen(text), temp, (_term_maxCharCol(pTerm) * _term_maxCharRow(pTerm)) - (strlen(text) * 2));
  /* Paste text into main text buffer up front */
  memcpy(pTerm->textBuffer, text, strlen(text));

  for(uint32_t i = 0 ; i < _term_maxCharCol(pTerm) * _term_maxCharRow(pTerm); i++) {
    if(pTerm->textBuffer[i] == '\n')
      pTerm->cursorPosition += _term_maxCharRow(pTerm) - (pTerm->cursorPosition % _term_maxCharRow(pTerm));

    if(pTerm->textBuffer[i] == '\t')
      pTerm->cursorPosition += 2;

    if(pTerm->textBuffer[i] < 32)
      continue;

    for(uint8_t x = 0; x < 5; x++) {
      for(uint8_t y = 0; y < 7; y++) {
        if(TERMINAL_FONT5X7[pTerm->textBuffer[i] - 32][x] & (1 << y)) {
          pTerm->setPixel(((pTerm->cursorPosition % _term_maxCharRow(pTerm)) * TERMINAL_FONT_SIZE_X) + x, ((pTerm->cursorPosition / _term_maxCharRow(pTerm)) * TERMINAL_FONT_SIZE_Y) + y); 
        }
      }
    }

    pTerm->cursorPosition++;
  }

  pTerm->draw();
}

void term_globalInit(PFN_terminalScreenSetPixel setPixelFn, PFN_terminalScreenDrawFunction drawFn, const uint32_t screenWidth, const uint32_t screenHeight) {
  term_init(&gTerminal, setPixelFn, drawFn, screenWidth, screenHeight);
}

void term_globalClear() {
  term_clear(&gTerminal);
}

void term_globalSetCursor(uint32_t x, uint32_t y) {
  term_setCursor(&gTerminal, x, y);
}

void puts(const char* text) {
  term_print(&gTerminal, text);
}
