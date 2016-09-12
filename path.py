import networkx as nx
import matplotlib.pyplot as plt
import operator
import jissen_config

class Path:
	def __init__(self):
		self.field = nx.grid_2d_graph(jissen_config.HEIGHT,jissen_config.WIDTH) 
		self.shut_nodes_set = set()					
		
			
	def draw_field(self):
		pos = dict( (n, n) for n in self.field.nodes() )
		nx.draw_networkx(self.field,pos=pos)
		
		plt.axis('off')
		plt.show()
	
	
	def shut_node(self,node):
		self.field.remove_node(node)
		self.field.add_node(node)
		self.shut_nodes_set.add(node)
		
		
	def open_node(self,node):
		#hamidasanaika
		def check_neighbour(neighbour):
			i,j = neighbour
			if i<0 or j<0 or i>=jissen_config.HEIGHT or j>= jissen_config.WIDTH:
				return False
			else:
				return True
		#honsyori		
		gap = [(1,0),(-1,0),(0,1),(0,-1)]
		tmp_neighbours = map(lambda x: map(operator.add,x,node),gap)
		neighbours = filter(check_neighbour,tmp_neighbours)
		for i in neighbours:
			self.field.add_edge(node,tuple(i))
		#atosyori		
		self.shut_nodes_set.remove(node)
		for i in self.shut_nodes_set:
			self.shut_node(i)
			
	def find_shortest_path(self,source,target):
		try:
			s_path = nx.shortest_path(self.field,source=source,target=target)
		except nx.NetworkXNoPath:
			print "no path"
			return 0
			
		return s_path
	
			
		
