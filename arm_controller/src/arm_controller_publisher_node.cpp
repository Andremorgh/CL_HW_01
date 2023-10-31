#include <ros/ros.h>
#include "std_msgs/Float64.h"

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "arm_controller_publisher_node");
    ros::NodeHandle nh;
   // Crea publisher per inviare comandi ai controller
    ros::Publisher joint0CommandPub = nh.advertise<std_msgs::Float64>("/arm/joint0_position_controller/command", 100);
    ros::Publisher joint1CommandPub = nh.advertise<std_msgs::Float64>("/arm/joint1_position_controller/command", 100);
    ros::Publisher joint2CommandPub = nh.advertise<std_msgs::Float64>("/arm/joint2_position_controller/command", 100);
    ros::Publisher joint3CommandPub = nh.advertise<std_msgs::Float64>("/arm/joint3_position_controller/command", 100);
     
    // Imposta la frequenza di aggiornamento (Hz) per la tua traiettoria
    double frequency = 10.0;  // Esempio: 1 Hz

    // Durata di un periodo della traiettoria (secondi)
    double period = 100.0 / frequency;

    // Valori di ampiezza massima e minima della traiettoria
    double max_amplitude = 10.0;
    double min_amplitude = -10.0;

    // Inizia dalla posizione minima
    double current_position = min_amplitude;
    bool increasing = true;

    ros::Rate loop_rate(frequency);

    while (ros::ok())
    {
        // Genera comandi di posizione a forma di onda triangolare
        std_msgs::Float64 position_command_j0;
        position_command_j0.data = current_position;
        // Pubblica il comando sul topic del controller del giunto
        joint0CommandPub.publish(position_command_j0);
         
        // Invio messaggi distinti anche se il contenuto è il medesimo per avere generalità
        std_msgs::Float64 position_command_j1;
        position_command_j1.data = current_position;
        joint1CommandPub.publish(position_command_j1);

        std_msgs::Float64 position_command_j2;
        position_command_j2.data = current_position;
        joint2CommandPub.publish(position_command_j2);

        std_msgs::Float64 position_command_j3;
        position_command_j3.data = current_position;
        joint3CommandPub.publish(position_command_j3);

        // Calcolo onda quadra
        if (increasing)
        {
            current_position += (2.0 * max_amplitude / period) * (1.0 / frequency);
            if (current_position >= max_amplitude)
            {
                current_position = max_amplitude;
                increasing = false;
            }
        }
        else
        {
            current_position -= (2.0 * max_amplitude / period) * (1.0 / frequency);
            if (current_position <= min_amplitude)
            {
                current_position = min_amplitude;
                increasing = true;
            }
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}