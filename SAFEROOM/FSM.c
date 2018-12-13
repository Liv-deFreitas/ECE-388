/*
 * FSM.c
 *
 * Created: 11/26/2018 7:43:12 PM
 *  Author: rjfur
 */ 

#include "FSM.h"
void STATE_Transition(STATE next)
{
	STATE_Current = next;
}