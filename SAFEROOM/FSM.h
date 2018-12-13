/*
 * FSM.h
 *
 *
 *  Author: rjfur
 */ 


#ifndef FSM_H_
#define FSM_H_

typedef enum state{
	DORMANT,
	DOORLOCK,
	//OCCUPYING,
	CLIMATECONTROL
	//SETTEMP
	
}STATE;

volatile STATE STATE_Current;
void STATE_Transition(STATE next);




#endif /* FSM_H_ */