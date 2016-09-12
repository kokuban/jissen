import path
import jissen_config
import robot
import operator




#muki
	direction = jissen_config.FORWARD

if __name__ == '__main__':


	#mawaru
	initial_node = (0,0)
	
	current_node=get_destination(initial_node,(8,0))
	current_node=get_destination(current_node,(0,1))
	current_node=get_destination(current_node,(8,2))
	current_node=get_destination(current_node,(0,3))
	current_node=get_destination(current_node,(8,4))
	current_node=get_destination(current_node,(0,5))
	
	#suteru
	current_node=get_destination(current_node,(3,0))
	
	#goal
	get_destination(current_node,(8,2))
	
	
	
def get_destination(source_node,dst_node):

	current_node = source_node
	
	while(1)
	
		pathes = path.find_shortest_path(current_node,dst_node)
		if pathes[0] == (-1,-1):
			return current_node,direction
		
		for i in range(len(pathes)-1):
			diff = map(operator.sub,pathes[i+1],pathes[i])
			
			#tateidou
			if diff[0] != 0:
				#ue	
				if diff[0] == 1:
					if jissen_move(jissen_config.FORWARD) == TRUE:
						current_node = pathes[i+1]
					else:
						break
				
				#sita
				else:
					if jissen_move(jissen_config.BACK) == TRUE:
						current_node = pathes[i+1]
					else:
						break
					
			#yokoidou
			else:
				#migi
				if diff[1] == 1:
					if jissen_move(jissen_config.RIGHT) == TRUE:
						current_node = pathes[i+1]
					else:
						break
					
				#hidari
				else:
					if jissen_move(jissen_config.LEFT) == TRUE:
						current_node = pathes[i+1]
					else:
						break
					
		if current_node == dst_node:
			return dst_node
			
def jissen_move(destination):
	if (destination-direction+4) % 4 == 0:
		return(robot.move_forward())
		
	if (destination-direction+4) % 4 == 1:
		robot.turn_right()
		direction = destination
		return(robot.move_forward())
		
	if (destination-direction+4) % 4 == 2:
		robot.turn_right()
		robot.turn_right()
		direction = destination
		return(robot.move_forward())
		
	if (destination-direction+4) % 4 == 3:
		robot.turn_left()
		direction = destination
		return(robot.move_forward())
	
				
	
				
