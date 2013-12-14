package robot;
import robocode.*;
import java.awt.Color;

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
	
		// Swppe gunand radar when an enemy is spotted
		gunDirection = -gunDirection;
		setTurnGunRight(99999*gunDirection);
		
		// Fire at target
		fire ( 2 ) ;
		
		// Track energy level
		previousEnergy = e.getEnergy();
	}
	
}
