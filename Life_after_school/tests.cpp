#include <iostream>
#include "services.h" // Assuming this is the header file for your Service class

void testAddEvent(Service& service) {
    Event event("Title", "Description", "https://example.com", 19, 4, 2024, 10, 30, 50);
    service.addEvent_Services(event);
    std::cout << "AddEvent test passed!" << std::endl;
}

void testRemoveEvent(Service& service) {
    service.addEvent_Services(Event("Title", "Description", "https://example.com", 19, 4, 2024, 10, 30, 50));
    service.removeEvent_Services(0);
    std::cout << "RemoveEvent test passed!" << std::endl;
}

void testUpdateEvent(Service& service) {
    service.addEvent_Services(Event("Title", "Description", "https://example.com", 19, 4, 2024, 10, 30, 50));
    Event updatedEvent("Updated Title", "Updated Description", "https://updated.com", 20, 4, 2024, 11, 30, 60);
    service.updateEvent_Services(0, updatedEvent);
    std::cout << "UpdateEvent test passed!" << std::endl;
}

void testIncreasePeople(Service& service) {
    service.addEvent_Services(Event("Title", "Description", "https://example.com", 19, 4, 2024, 10, 30, 50));
    service.increasePeople_Services(0);
    std::cout << "IncreasePeople test passed!" << std::endl;
}

void testDecreasePeople(Service& service) {
    service.addEvent_Services(Event("Title", "Description", "https://example.com", 19, 4, 2024, 10, 30, 50));
    service.decreasePeople_Services(0);
    std::cout << "DecreasePeople test passed!" << std::endl;
}

/*int main() {
    Service service;
    testAddEvent(service);
    testRemoveEvent(service);
    testUpdateEvent(service);
    testIncreasePeople(service);
    testDecreasePeople(service);
    return 0;
}*/
