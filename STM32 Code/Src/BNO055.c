/*!
 @file 		BNO055.c
 @brief		This file provides the functionality to use a BNO055 inertial measurement unit.
 @author	Sean Wahl
 @date		June 14, 2023
*/

#include "BNO055.h"

/*!
 @brief BNO055 Object initialization function.
 This function configures a BNO055 struct to include the I2C lines attached to the IMU.
 @param 	hi2c: 		I2C handle pointer
 @retval 				Returns a BNO055 struct for future command use. 	
*/
BNO055_t BNO_Init(I2C_HandleTypeDef* hi2c) {
	BNO055_t myBNO;
	myBNO.hi2c = hi2c;

	myBNO = BNO_OprMode(myBNO, CONFIGMODE);

	return myBNO;
}

/*!
 @brief BNO055 Change operating mode function.
 This function writes to the BNO055 to change the operating mode its in to a user specified one.
 @param 	myBNO:		BNO055 struct type
 @retval 				Returns the BNO struct back (though not necessary)
*/
BNO055_t BNO_OprMode(BNO055_t myBNO, uint8_t mode) {
	uint8_t data[1];
	data[0] = CONFIGMODE;
	HAL_I2C_Mem_Write(myBNO.hi2c, BNO055_ADDR, BNO055_OPR_MODE, 1, data, 1, HAL_MAX_DELAY);
	HAL_Delay(20);
	if (mode != CONFIGMODE) {
		data[0] = mode;
		HAL_I2C_Mem_Write(myBNO.hi2c, BNO055_ADDR, BNO055_OPR_MODE, 1, data, 1, HAL_MAX_DELAY);
		HAL_Delay(8);
	}

	myBNO.opr_mode = mode;
	return myBNO;
}

/*!
 @brief BNO055 Calibration status.
 This reads from the BNO055's calibration registers and returns them as part of the BNO struct. All
 statuses will be 3 when the BNO is fully calibrated (assuming NDOF mode).
 @param 	myBNO:		BNO055 struct type
 @retval 				Returns the BNO struct for access to the calibration statuses
*/
BNO055_t BNO_CalStat(BNO055_t myBNO) {
	uint8_t cal_byte;

	HAL_I2C_Mem_Read(myBNO.hi2c, BNO055_ADDR, BNO055_CALIB_STAT, 1, &cal_byte, 1, HAL_MAX_DELAY);

	myBNO.mag_stat = (cal_byte & 0x03);
	myBNO.acc_stat = (cal_byte & 0x0C)>>2;
	myBNO.gyr_stat = (cal_byte & 0x30)>>4;
	myBNO.sys_stat = (cal_byte & 0xC0)>>6;

	return myBNO;
}

/*!
 @brief BNO055 Euler angles.
 This function reads from the BNO055's euler angle registers (heading, roll, and pitch) and returns 
 them as part of the BNO struct. The system should be calibrated before using this function.
 @param 	myBNO:		BNO055 struct type
 @retval 				Returns the BNO struct back for access to the euler angles.
*/
BNO055_t BNO_GetEul(BNO055_t myBNO) {
	uint8_t mag_bytes[6];

	HAL_I2C_Mem_Read(myBNO.hi2c, BNO055_ADDR, BNO055_EUL_Heading_LSB, 1, mag_bytes, 6, HAL_MAX_DELAY);

	myBNO.eul_heading = ((mag_bytes[1]<<8)|mag_bytes[0]);
	myBNO.eul_heading = myBNO.eul_heading/16 - 180;
	myBNO.eul_roll = ((mag_bytes[3]<<8)|mag_bytes[2]);
	myBNO.eul_roll = myBNO.eul_roll/16;
	myBNO.eul_pitch = ((mag_bytes[5]<<8)|mag_bytes[4]);
	myBNO.eul_pitch = myBNO.eul_pitch/16;

	return myBNO;
}

