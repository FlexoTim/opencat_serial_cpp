/**
 * @brief Serial library for opencat
 * @file
 * @author C.C
 * @date 2022.05.22
 **/
#pragma once
#include "serial/serial.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace OpenCat
{
enum Command : uint8_t
{
    SHUT_DOWN,                // rest and shutdown all servos
    SWITCH_GYRO,              // switch whether to use IMU data
    PAUSE_MOTION,             // TODO: difference between shutdown?
    CALIBRATE,                // Calibration mode
    SWITCH_RECOVERING,        // TODO: check if this can be disabled
    REPEAT_SKILL,             // repeat last called skill
    PLAY_CUSTOM_SKILL,        // play custom defined skill
    MOVE_JOINT_SEQUENCE,      // move joints in sequence
    MOVE_JOINTS_SIMULTANEOUS, // move joints all at once
    SET_JOINTS,               // set all joints at once
    PLAY_MELODY,              // play built-in melody
    PLAY_CUSTOM_SOUND,        // play the cutom provided sound

    STEPPING,    // stepping on the same spot
    BACK,        // going back
    BACK_LEFT,   // going back and left
    BACK_RIGHT,  // going back and right
    CRAWL,       // crawl forward
    CRAWL_LEFT,  // crawl left
    CRAWL_RIGHT, // crawl right
    WALK,        // walk forward
    WALK_LEFT,   // walk left
    WALK_RIGHT,  // walk right
    TROT,        // trot forward
    TROT_LEFT,   // trot left
    TROT_RIGHT,  // trot right
    BOUND,       // not recommended

    BALANCE,    // balancing mode
    BUTT_UP,    // raise hip
    CALIB_POSE, // Calibration pose, make easy to calibrate joints
    REST,       // rest mode TODO: difference between SHUT_DOWN
    SIT,
    SLEEP,
    STRETCH,
    ZERO, // template for designing new posture

    CHECK_AROUND,
    GREETING,
    PEE,
    PUSH_UP,
    MIMIC_DEATH,
    BACK_FLIP
};

// alias for command arguments
using TaskArgs = std::vector<int16_t>;

struct Task
{
    Task(Command _cmd) : cmd(_cmd), arguments{}, delay(0){};
    Task(Command _cmd, float _delay) : cmd(_cmd), arguments{}, delay(_delay){};
    Task(Command _cmd, TaskArgs _args, float _delay)
        : cmd(_cmd), arguments{_args.begin(), _args.end()}, delay(_delay){};
    Command cmd;
    TaskArgs arguments;
    float delay;
};

/**
 * @brief wrapper class to communicate with OpenCat robot
 * @inherit ::Serial::Serial, protected as we don't need to send arbitrary data
 **/
class Robot : protected ::serial::Serial
{
  public:
    /**
     * @brief default constructor
     * @param serial_port: serial port to connect the dog
     **/
    Robot(string serial_port);

    /**
     * @brief send task to robot
     * @param task: %Task data pack
     * @return response message from robot
     **/
    std::string SendTask(const Task &task, bool verbose = false);

    void SendMultipleTasks(const vector<Task> &tasks, bool verbose = false);

  protected:
};

/**
 * @brief find and list available serial ports
 * @return %vector with path to the port as %string
 * @ref:
 *   https://stackoverflow.com/questions/15342804/c-linux-detect-all-serial-ports
 **/
const vector<string> ListSerialPorts();
} // namespace OpenCat
