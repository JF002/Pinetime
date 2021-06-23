#include "Clock.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "BatteryIcon.h"
#include "BleIcon.h"
#include "NotificationIcon.h"
#include "Symbols.h"
#include "components/settings/Settings.h"
#include "components/battery/BatteryController.h"
#include "components/motion/MotionController.h"
#include "components/ble/BleController.h"
#include "components/ble/NotificationManager.h"
#include "../DisplayApp.h"
#include "WatchFaceDigital.h"
#include "WatchFaceAnalog.h"

using namespace Pinetime::Applications::Screens;

Clock::Clock(DisplayApp* app,
             Controllers::DateTimeController& dateTimeController,
             Controllers::Battery& batteryController,
             Controllers::Ble& bleController,
             Controllers::NotificationManager& notificatioManager,
             Controllers::Settings& settingsController,
             Controllers::HeartRateController& heartRateController,
             Controllers::MotionController& motionController)
  : Screen(app),
    dateTimeController {dateTimeController},
    batteryController {batteryController},
    bleController {bleController},
    notificatioManager {notificatioManager},
    settingsController {settingsController},
    heartRateController {heartRateController},
    motionController {motionController},
    screen {[this, &settingsController]() {
      switch (settingsController.GetClockFace()) {
        case Controllers::Settings::ClockFace::Digital:
          return WatchFaceDigitalScreen();
          break;
        case Controllers::Settings::ClockFace::Analog:
          return WatchFaceAnalogScreen();
          break;
      }
      return WatchFaceDigitalScreen();
    }()} {
  settingsController.SetAppMenu(0);
}

Clock::~Clock() {
  lv_obj_clean(lv_scr_act());
}

bool Clock::Refresh() {
  screen->Refresh();
  return running;
}

bool Clock::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return screen->OnTouchEvent(event);
}

std::unique_ptr<Screen> Clock::WatchFaceDigitalScreen() {
  return std::make_unique<Screens::WatchFaceDigital>(app,
                                                     dateTimeController,
                                                     batteryController,
                                                     bleController,
                                                     notificatioManager,
                                                     settingsController,
                                                     heartRateController,
                                                     motionController);
}

std::unique_ptr<Screen> Clock::WatchFaceAnalogScreen() {
  return std::make_unique<Screens::WatchFaceAnalog>(app,
                                                    dateTimeController,
                                                    batteryController,
                                                    bleController,
                                                    notificatioManager,
                                                    settingsController,
                                                    heartRateController,
                                                    motionController);
}

/*
// Examples for more watch faces
std::unique_ptr<Screen> Clock::WatchFaceMinimalScreen() {
  return std::make_unique<Screens::WatchFaceMinimal>(app,
                                                     dateTimeController,
                                                     batteryController,
                                                     bleController,
                                                     notificatioManager,
                                                     settingsController,
                                                     heartRateController,
                                                     motionController);
}

std::unique_ptr<Screen> Clock::WatchFaceCustomScreen() {
  return std::make_unique<Screens::WatchFaceCustom>(app,
                                                    dateTimeController,
                                                    batteryController,
                                                    bleController,
                                                    notificatioManager,
                                                    settingsController,
                                                    heartRateController,
                                                    motionController);
}
*/
