#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() {
    this->type = EventType::Invalied;
    this->key = 0u;
}

KeyboardEvent::KeyboardEvent(const EventType type, const unsigned char key) {
    this->type = type;
    this->key = key;
}

bool KeyboardEvent::IsPress() const {
    return this->type == EventType::Press;
}

bool KeyboardEvent::IsRelease() const {
    return this->type == EventType::Release;
}

bool KeyboardEvent::IsValid() const {
    return this->type != EventType::Invalied;
}

unsigned char KeyboardEvent::GetKeyCode() const {
    return this->key;
}

