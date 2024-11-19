#include <iostream>
#include <cassert>
#include "services.h"

void testAddEvent() {
    Service service;
    Event event("eve", "Desrgbcription", "http://example.com", 3, 1, 2024, 12, 30, 15);

    service.addEvent_Services(event);

    assert(service.getSize_Services() != 0);
}

void testRemoveEvent() {
    Service service;
    Event event("eveevev", "Descrrbription", "http://example.com", 3, 1, 2024, 12, 30, 15);
    service.addEvent_Services(event);

    service.removeEvent_Services(0);

    assert(service.getSize_Services() != 1);
}

void testIncreasePeople() {
    Service service;
    Event event("Nent", "Desceeription", "http://example.com", 3, 1, 2024, 12, 30, 15);
    service.addEvent_Services(event);

    service.increasePeople_Services(0);

    assert(service.getEvent_Services(0).getPeoples() == 1);
}

void testDecreasePeople() {
    Service service;
    Event event("Nv4vvnt", "Descrirrrrrewwption", "http://example.com", 3, 1, 2024, 12, 30, 15);
    service.addEvent_Services(event);

    service.decreasePeople_Services(0);

    assert(service.getEvent_Services(0).getPeoples() == 0);
}

/*int main() {
    testAddEvent();
    testRemoveEvent();
    testIncreasePeople();
    testDecreasePeople();

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}*/
