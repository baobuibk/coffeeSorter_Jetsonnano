/*
 * Create by: Duc An Nguyen
 * Date on: 5/4/2021 
 *
 *
 * This function is used for communicating with external devices
 * It consist of three parts: open camera, Uart and timer. 
 */






class external_devices
{
	public:
		external_device();
		~external_device();

		uint8 open_camera();


};
