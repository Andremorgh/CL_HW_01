#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

void jointStateCallback(const sensor_msgs::JointState::ConstPtr& jointState) {
    // Stampa le posizioni dei giunti
    for (size_t i = 0; i < jointState->position.size(); ++i) {
        ROS_INFO("Joint %zu: %f", i, jointState->position[i]);
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;

    // Crea un subscriber per il topic "joint_states"
    ros::Subscriber jointStateSub = nh.subscribe("/arm/joint_states", 100, jointStateCallback);

    ros::spin();  // Mantieni il nodo attivo

    return 0;
}
