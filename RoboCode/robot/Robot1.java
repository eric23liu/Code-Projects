package robot;
import robocode.*;
import java.awt.Color;

// Idea:
// Construct a linked list of all robots in the arena.
// Choose best robot to attack based on their stats.
// Pop entry when robot is destroyed, and update stats saved in the linked list

public class Robot1 extends AdvancedRobot
{
	double previousEnergy = 100;
	int movementDirection = 1;
	int gunDirection = 1;
	
	public void run() { setTurnGunRight(99999); }

	public void onScannedRobot(
		ScannedRobotEvent e) {
		// Stay at perpendicular to the enemy
		setTurnRight(e.getBearing()+90-
		30*movementDirection);
         
		// If the bot has small energy drop, assume it fired
		double changeInEnergy =
		previousEnergy-e.getEnergy();
		
		if (changeInEnergy>0 &&	changeInEnergy<=3) {
			// Dodge
			movementDirection = -movementDirection;
			setAhead((e.getDistance()/4+25)*movementDirection);
		}
	
		// Sweep gun and radar when an enemy is spotted
		gunDirection = -gunDirection;
		setTurnGunRight(99999*gunDirection);
		
		// Fire at target
		// TO DO: calculate firepower based on distance from enemy
		fire ( 2 ) ;
		
		// Track energy level
		previousEnergy = e.getEnergy();
	}
	
}
