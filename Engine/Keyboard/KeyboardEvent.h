#pragma once

class KeyboardEvent {
  public:
    enum class EventType { Press, Release, Invalied };
    KeyboardEvent();
    KeyboardEvent(const EventType type, const unsigned char key);
    bool IsPress() const;
    bool IsRelease() const;
    bool IsValid() const;
    unsigned char GetKeyCode() const;

  private:
    EventType type;
    unsigned char key;
};