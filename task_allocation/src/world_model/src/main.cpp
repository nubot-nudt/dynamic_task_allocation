#include <world_model.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"world_model_node");
    ros::Time::init();
    World_Model World_Model(argc,argv);
    ros::spin();
    return 0;
}
