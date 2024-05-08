#include "examples.h"
#include "esp_config.h"

void display_arrivals(VirtualMatrixPanel *virtualDisp);
struct Arrival
{
    int stop_id;
    char line[4];
    char destination[32];
    uint8_t minutesRealTime;
    char timeScheduled[5];
};

void setupZDITM(VirtualMatrixPanel *virtualDisp) {}
void loopZDITM(VirtualMatrixPanel *virtualDisp)
{
    // display_arrivals(virtualDisp);
    delay(1000);
}
#define COLOR_DESTINATION 0xFECE45 // orange

// Arrival arrivals[2] = {
//     {1, {'2', '1', '3', '7'}, "Osiedle przyjazni", 6, {'2', '1', ':', '3', '7'}},
//     {2, {'2', '1', '3', '7'}, "Osiedle przyjazni", 20, {'2', '1', ':', '3', '7'}}};

// void display_arrivals(VirtualMatrixPanel *virtualDisp)
// {
//     // sendRequest();
//     // clear disp
//     // virtualDisp->fillScreen(virtualDisp->color444(0, 0, 0));
//     uint16_t destinationColor;
//     hex_to_565(COLOR_DESTINATION, &destinationColor);
//     for (int i = 0; i < (PANEL_RES_Y * NUM_ROWS) / 8 && i < numberOfArrivals; i++)
//     {
//         ESP_LOGI(TAG, "Arrival %d", i);
//         // ESP_LOGW("DISP", "Line %s, destination %s ", arrivals[i].line, arrivals[i].destination);
//         uint16_t textColor;
//         uint16_t backgroundColor;

//         // switch (i){
//         //     case 0:
//         //       strncpy(arrivals[i].line, "B", 4);
//         //       break;
//         //     case 1:
//         //       strncpy(arrivals[i].line, "521", 4);
//         //       break;
//         //     case 2:
//         //       strncpy(arrivals[i].line, "12", 4);
//         //       break;
//         //     case 3:
//         //       strncpy(arrivals[i].line, "5", 4);
//         //       break;
//         //     case 4:
//         //       strncpy(arrivals[i].line, "528", 4);
//         //       break;
//         //     case 5:
//         //       strncpy(arrivals[i].line, "806", 4);
//         //       break;
//         //     case 6:
//         //       strncpy(arrivals[i].line, "87", 4);
//         //       break;
//         //   }

//         get_line_colors(arrivals[i].line, &textColor, &backgroundColor);
//         encode_polish_letters(arrivals[i].destination);
//         virtualDisp->setTextColor(textColor, backgroundColor);
//         virtualDisp->fillRect(0, (i * 8), 192, (i * 8) + 8, 0);
//         virtualDisp->fillRect(0, (i * 8), get_line_txt_len(arrivals[i].line) * 6 + 1, (i * 8) + 8, backgroundColor);
//         virtualDisp->setCursor(1, (i + 1) * 8);
//         virtualDisp->print(arrivals[i].line);
//         virtualDisp->fillRect(21, (i * 8), PANEL_RES_Y * NUM_ROWS - 21, (i * 8) + 8, 0);
//         virtualDisp->setCursor(21, (i + 1) * 8);
//         virtualDisp->setTextColor(destinationColor, backgroundColor);
//         virtualDisp->print(arrivals[i].destination);
//         // uint16_t buf = 0, len = 0;
//         // int16_t buf2 = 0;

//         // ESP_LOGI(TAG, "Minutes RT: %d\n", arrivals[i].minutesRealTime);
//         if (arrivals[i].minutesRealTime == 0 && arrivals[i].timeScheduled[0] != 'u')
//         {
//             // time schechueld as const string
//             // char *s = arrivals[i].timeScheduled;
//             // virtualDisp->getTextBounds((const char *)arrivals[i].destination, (uint16_t)0, (uint16_t)0, &buf2, &buf2, &len, &buf);
//             virtualDisp->setCursor(PANEL_RES_X * NUM_COLS - 30, (i + 1) * 8);
//             virtualDisp->setTextColor(destinationColor, backgroundColor);
//             virtualDisp->print(arrivals[i].timeScheduled);
//         }
//         else if (arrivals[i].minutesRealTime > 0)
//         {
//             // za 00 min
//             if (arrivals[i].minutesRealTime < 10)
//                 virtualDisp->setCursor(PANEL_RES_X * NUM_COLS - 24, (i + 1) * 8);
//             else
//                 virtualDisp->setCursor(PANEL_RES_X * NUM_COLS - 30, (i + 1) * 8);
//             // virtualDisp->print("za ");
//             virtualDisp->print(arrivals[i].minutesRealTime);
//             virtualDisp->print(" min");
//         }
//         else
//         {
//             virtualDisp->setCursor(PANEL_RES_X * NUM_COLS - 24, (i + 1) * 8);
//             virtualDisp->print("<<< ");
//         }
//         // virtualDisp->setCursor(PANEL_RES_X * NUM_COLS - (virtualDisp->get
//     }
// }