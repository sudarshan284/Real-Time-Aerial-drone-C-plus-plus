#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

// Constants for drone operations.
constexpr float TAKEOFF_SPEED = 5.0f;  // Meters per second
constexpr float LANDING_SPEED = -2.0f; // Meters per second
constexpr float MAX_ALTITUDE = 100.0f; // Maximum flight altitude

// Drone class representing the state and behavior of a real-time aerial system.
class Drone
{
private:
    float altitude;
    bool is_flying;

public:
    Drone() : altitude(0.0f), is_flying(false) {}

    // Simulate takeoff by gradually increasing altitude until the maximum is reached.
    void takeOff()
    {
        is_flying = true;
        while (altitude < MAX_ALTITUDE)
        {
            altitude += TAKEOFF_SPEED; // Increase altitude.
            std::cout << "Ascending. Current altitude: " << altitude << "m\n";
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for a second.
        }
        std::cout << "Drone reached maximum altitude of " << MAX_ALTITUDE << "m.\n";
    }

    // Simulate landing by decreasing altitude until the drone reaches the ground.
    void land()
    {
        while (altitude > 0)
        {
            altitude += LANDING_SPEED; // Decrease altitude.
            if (altitude < 0)
                altitude = 0; // Ensure altitude does not go below 0.
            std::cout << "Descending. Current altitude: " << altitude << "m\n";
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for a second.
        }
        is_flying = false;
        std::cout << "Drone has landed.\n";
    }

    // Function to fly the drone to a specified altitude.
    void flyToAltitude(float target_altitude)
    {
        if (!is_flying)
        {
            std::cout << "Drone is not flying. Can't change altitude.\n";
            return;
        }

        if (target_altitude > MAX_ALTITUDE || target_altitude < 0)
        {
            std::cout << "Target altitude is outside the valid range.\n";
            return;
        }

        float direction = target_altitude > altitude ? 1 : -1;
        while (altitude != target_altitude)
        {
            altitude += direction; // Ascend or descend.
            std::cout << "Flying. Current altitude: " << altitude << "m\n";
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for a second.
        }
        std::cout << "Reached target altitude of " << target_altitude << "m.\n";
    }
};

int main()
{
    Drone drone;
    drone.takeOff();
    drone.flyToAltitude(50.0f);
    drone.land();
    return 0;
}
