/******************************************************************************
Author		: Lichao Ma
Date  		: Mar 25,2016
version		: v0.2
Description :
	Test file for testing the car model,PID controller,and PID self optimization
	algorithm.The simulated result are both printed on screen and saved to the
	log file for further use.
*****************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include "car.h"
#include "pid.h"
#include "Vehicle.h"
using namespace std;

void testSimpleCar(){
	double kP=55;
	double kI=1;
	double kD=100;
	//double kP=100;
	//double kI=0;
	//double kD=0;
	vector<double> speed;
	vector<double> distance;
	double target=100;
	size_t simulationTime=400;
	float simulationPeriod=0.1;

	Car simpleCar(1,0.1,0.01,simulationPeriod);//Mass(1),Friction(0.1),Resistance(0.01),Period(0.1)
	//simpleCar.setSystemLag(2);
	//simpleCar.setNoise(0.4,0.7,0.1);	//Force noise,distance and speed reading noise
	simpleCar.setToStandardCar();
	PID positionPID(kP,kI,kD,simulationPeriod);

	//////// Testing the PID self optimization algorithm //////
	double twiddleTolerance=0.5;
	//if(pid.twiddle(simpleCar,target,twiddleTolerance,simulationTime)){
	//	cout <<"twiddle success\n";
	//}else{
	//	cout << "twiddle() runtime exceeded!\n";
	//}
	printf("P %.3f\t\tI %.3f\t\tD %.3f\n",positionPID.getP(),positionPID.getI(),positionPID.getD());

	////////////// Simulate the car movement ////////////////
	simpleCar.resetOrigin();
	double targetQue[]={100};
	size_t queSize=sizeof(targetQue)/sizeof(targetQue[0]);
	cout<<"Target number = "<<queSize<<endl;
	cout<<"PID simulation:\n";
	cout<<"time\tForce\tVelocity\tDistance\n";
	for(size_t j=0;j<queSize;j++){
		target=targetQue[j];
		cout<<"\nTarget position = "<<target<<endl;
		for(size_t i=0;i<simulationTime/queSize;i++){
			//cout<<update(simpleCar,force)<<endl;
			double output=positionPID.calculate(target,simpleCar.getDistance());
			simpleCar.update(output);
			printf("%d\t%.1f\t\t%.1f\t\t%.1f\n",
					i,simpleCar.getForce(),simpleCar.getVelocity(),simpleCar.getDistance());
			speed.push_back(simpleCar.getVelocity());
			distance.push_back(simpleCar.getDistance());
		}
	}

	///////// Save the result to result.csv for visualizing the data ////////
	ofstream file("result.csv");
	for(size_t i=0;i<simulationTime;i++)
		file<<speed[i]<<","<<distance[i]<<endl;
	file.close();
}

void testVehicle(){
	Vehicle v;
	vector<double> x;
	vector<double> y;
	v.setToStandardVehicle();
	v.setState(0,0,0,0,1,0);

	size_t simulationTime=200;
	for(size_t i=0;i<simulationTime;i++){
		v.driveWithoutPID(3,3.14/180.0*1);

		printf("%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n",
				v.getX(),v.getY(),
				v.getOrientation(),v.getSpeedLongitudinal(),v.getSpeedYaw());
		//printf("%.1f\t\t%.1f\t\t%.1f\n",v.getSpeedLongitudinal(),v.getSpeedLateral(),v.getSpeedYaw());
		x.push_back(v.getX());
		y.push_back(v.getY());
	}

	///////// Save the result to result.csv for visualizing the data ////////
		ofstream file("vehicle result.csv");
		for(size_t i=0;i<simulationTime;i++)
			file<<x[i]<<","<<y[i]<<endl;
		file.close();
}


int main(){

	testVehicle();

}
