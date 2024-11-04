#include "maze.hpp"
#include "cyclic_double_queue.hpp"
using namespace cs251;






bool valid(tuple a, Direction b, int dimX, int dimY, int dimZ);
Direction new_direction(Direction a);
bool mark(size_t index);
tuple new_tuple(tuple a, Direction b);



void maze::initialize(const size_t dimX, const size_t dimY, const size_t dimZ, unsigned seed)
{ 
	m_dimX = dimX;
	m_dimY = dimY;
	m_dimZ = dimZ;
	
	m_map = new unsigned[dimX * dimY * dimZ];
	cyclic_double_queue<tuple> stack(5, 2, 2);

	for(int i = 0; i < dimX; i++) {
		for(int j = 0; j < dimY; j++) {
			for(int k = 0; k < dimZ; k++) {
				m_map[(i) + (j * m_dimX) + (k * dimX * dimY)] = 
					unsigned(1<<0) + unsigned(1<<1) + unsigned(1<<2) + unsigned(1<<3) + unsigned(1<<4) +unsigned(1<<5);
			}
		}
	}

	
	tuple a = {0, 0, 0};
	stack.enqueue_front(a);

	while (!stack.empty()) {
		Direction new_dir = get_next_direction(seed);
		tuple front = stack.front();
		size_t temp = m_map[get_index(front.x, front.y, front.z)];
		m_map[(front.x) + (front.y * m_dimX) + (front.z * m_dimX * m_dimY)] |= unsigned(Direction::Mark);

		tuple neighbor = new_tuple(front, new_dir);

		int i = 0;
		while ((!valid(front, new_dir, m_dimX, m_dimY, m_dimZ)  && (i < 6)) || ((mark(m_map[get_index(neighbor.x, neighbor.y, neighbor.z)])) && (i < 6))) {
			new_dir = new_direction(new_dir);
			neighbor = new_tuple(front, new_dir);
			i++;
		}
		if (i == 6) {
			stack.pop_front();
			continue;
		}

		m_map[(front.x) + (front.y * m_dimX) + (front.z * m_dimX * m_dimY)] &= ~unsigned(new_dir);
		Direction opp_dir = get_opposite_dir(new_dir);
		m_map[(neighbor.x) + (neighbor.y * m_dimX) + (neighbor.z * m_dimX * m_dimY)] &= ~unsigned(opp_dir);
		neighbor = new_tuple(front, new_dir);
		stack.enqueue_front(neighbor);
	}
	
}

bool maze::solve(const size_t startX, const size_t startY, const size_t startZ, const size_t endX, const size_t endY, const size_t endZ)
{
	previous = new unsigned[m_dimX * m_dimY * m_dimZ];

	for(int i = 0; i < m_dimX; i++) {
		for(int j = 0; j < m_dimY; j++) {
			for(int k = 0; k < m_dimZ; k++) {
				unsigned map_index = m_map[(i) + (j * m_dimX) + (k * m_dimX * m_dimY)];
				m_map[(i) + (j * m_dimX) + (k * m_dimX * m_dimY)] &= ~unsigned(Direction::Mark);
			}
		}
	}
	
	cyclic_double_queue<unsigned> queue(5, 2, 2);
	unsigned start = get_index(startX, startY, startZ);
	queue.enqueue_front(start);
	unsigned end = get_index(endX, endY, endZ);

	bool found = false;

	
	while (!queue.empty()) {
		unsigned index = queue.dequeue_back();
		m_map[index] |= unsigned(Direction::Mark);

		if (index == end) {
			found = true;
			break;
		}
		
		Direction new_dir = Direction{};
		unsigned temp_index;
		unsigned value;
		
		int i = 0;
		while (i < 6) {
			new_dir = new_direction(new_dir);
			
			if ((m_map[index] & unsigned(new_dir)) == 0) {
				temp_index = get_new_index_(index, new_dir);
				if ((m_map[temp_index] & unsigned(Direction::Mark)) != 0) {
					i++;
					continue;
				}
			} else {
				i++;
				continue;
			}

			previous[temp_index] = index;
			queue.enqueue_front(temp_index);
			i++;
		}

	}

	for(int i = 0; i < m_dimX; i++) {
		for(int j = 0; j < m_dimY; j++) {
			for(int k = 0; k < m_dimZ; k++) {
				unsigned map_index = m_map[(i) + (j * m_dimX) + (k * m_dimX * m_dimY)];
				if ((map_index & unsigned(Direction::Mark)) != 0) {
					m_map[(i) + (j * m_dimX) + (k * m_dimX * m_dimY)] -= unsigned(Direction::Mark);
				}
			}
		}
	}

	while (end != start) {
		m_map[end] |= unsigned(Direction::Mark);
		end = previous[end];
	}
	m_map[start] |= unsigned(Direction::Mark);

	return found;
	
}



std::string maze::print_walls(const size_t z) const {
	std::string walls;
	int* a = new int[m_dimX];
	for (int i = 0; i < m_dimX; i++) {
	    a[i] = 1;
	}
	
	walls += add_line(m_dimX, a);

	for(int i = 0; i < m_dimY; i++) {
		
		walls += "|";
		
		a = new int[m_dimX];
		
		for (int p = 0; p < m_dimX; p++) {
	        a[p] = 0;
	    }
	    
	    
		for(int j = 0; j < m_dimX; j++) {
			bool fro = false;
			bool bac = false;
			
			size_t index = m_map[get_index(j, i, z)];

			if ((index & size_t(Direction::Front)) != 0) {
				fro = true;
			}
			if ((index & size_t(Direction::Back)) != 0) {
				bac = true;
			}
			if (fro && bac) {
				walls += " X ";
			} else if (fro && !bac) {
				walls += " F ";
			} else if (bac && !fro) {
				walls += " B ";
			} else {
				walls += "   ";
			}
			
			if ((index & size_t(Direction::Right)) != 0){
			    walls += "|";
		    } else {
				walls += " ";
			}
		    
		    if ((index & size_t(Direction::Top)) != 0){
			    a[j] = 1;
		    }

		}
		walls += "\n";
		walls += add_line(m_dimX, a);
	} 
	return walls;
}

std::string maze::add_line(int dimY, int* a) const {
	std::string walls;
	for (int i = 0; i < m_dimX; i++) {
	    if (a[i] == 1) {
		    walls += "+---";
	    }
	    else {
	        walls += "+   ";
	    }
	}
	walls += "+\n";
	return walls;
}


Direction maze::get_opposite_dir(Direction a) const{
	if (a == Direction::Right) {
		return Direction::Left;
	}
	else if (a == Direction::Left) {
		return Direction::Right;
	}
	else if (a == Direction::Top) {
		return Direction::Bottom;
	}
	else if (a == Direction::Bottom) {
		return Direction::Top;
	}
	else if (a == Direction::Back){
		return Direction::Front;
	}
	else if (a == Direction::Front){
		return Direction::Back;
	}
	return Direction::Front;

}



std::string maze::print_marks(const size_t z) const
{
	std::string walls;
	
	int* a = new int[m_dimX];
	
	for (int i = 0; i < m_dimX; i++) {
	    a[i] = 1;
	}
	
	walls += add_line(m_dimX, a);

	for(int i = 0; i < m_dimY; i++) {
		
		walls += "|";
		
		a = new int[m_dimX];
		
		for (int p = 0; p < m_dimX; p++) {
	        a[p] = 0;
	    }
	    
	    
		for(int j = 0; j < m_dimX; j++) {
			bool marked = false;
			
			size_t index = m_map[get_index(j, i, z)];

			if ((index & size_t(Direction::Mark)) != 0) {
				marked = true;
			}

			if (marked) {
				walls += " # ";
			} else {
				walls += "   ";
			}
			
			if ((index & size_t(Direction::Right)) != 0){
			    walls += "|";
		    } else {
				walls += " ";
			}
		    
		    if ((index & size_t(Direction::Top)) != 0){
			    a[j] = 1;
		    }

		}
		walls += "\n";
		walls += add_line(m_dimX, a);
	} 
	return walls;
}

void maze::get_dim(size_t& dimX, size_t& dimY, size_t& dimZ) const
{
	dimX = m_dimX;
	dimY = m_dimY;
	dimZ = m_dimZ;
}

Direction maze::get_next_direction(unsigned& seed)
{
	//Please do not modify this function! 
	//Any modification of this function may result in a zero for all grading cases.
	std::mt19937 gen(seed);
	seed = gen();
	return static_cast<Direction>(1 << seed % 6);
}


size_t maze::get_index(const size_t x, const size_t y, const size_t z) const
{
	return (x) + (y * m_dimX) + (z * m_dimX * m_dimY);
    
}


bool maze::valid(tuple a, Direction b, int dimX, int dimY, int dimZ) const {
	unsigned dir = unsigned(b);
	if ((dir == unsigned(Direction::Left)) && (a.x == 0))  {
		return false;
	} else if ((dir == unsigned(Direction::Right)) && (a.x == dimX - 1))  {
		return false;
	} else if ((dir == unsigned(Direction::Bottom)) && (a.y == 0))  {
		return false;
	} else if ((dir == unsigned(Direction::Top)) && (a.y == dimY - 1))  {
		return false;
	} else if ((dir == unsigned(Direction::Back)) && (a.z == dimZ - 1))  {
		return false;
	} else if ((dir == unsigned(Direction::Front)) && (a.z == 0))  {
		return false;
	} else {
		return true;
	}
}

Direction maze::new_direction(Direction a) const {
	if (a == Direction::Right) {
		return Direction::Left;
	}
	else if (a == Direction::Left) {
		return Direction::Top;
	}
	else if (a == Direction::Top) {
		return Direction::Bottom;
	}
	else if (a == Direction::Bottom) {
		return Direction::Back;
	}
	else if (a == Direction::Back){
		return Direction::Front;
	}
	else {
		return Direction::Right;
	}
}

bool maze::mark(size_t index) const {
	if ((index & size_t(Direction::Mark)) != 0) {
		return true;
	}
	return false;
}

tuple maze::new_tuple(tuple a, Direction b) const {
	tuple c;
	if (b == Direction::Right) {
		c = {a.x + 1, a.y, a.z};
	}
	else if (b == Direction::Left) {
		c = {a.x - 1, a.y, a.z};
	}
	else if (b == Direction::Top) {
		c = {a.x, a.y + 1, a.z};
	}
	else if (b == Direction::Bottom) {
		c = {a.x, a.y - 1, a.z};
	}
	else if (b == Direction::Back) {
		c = {a.x, a.y, a.z + 1};
	}
	else if (b == Direction::Front) {
		c = {a.x, a.y, a.z - 1};
	}
	return c;
}

unsigned maze::get_new_index_(unsigned a, Direction b) const {
	if (b == Direction::Right) {
		a++;
		return a;
	}
	else if (b == Direction::Left) {
		return a - 1;
	}
	else if (b == Direction::Top) {
		return a + m_dimX;
	}
	else if (b == Direction::Bottom) {
		return a - m_dimX;
	}
	else if (b == Direction::Back) {
		return a + (m_dimX * m_dimY);
	}
	else if (b == Direction::Front) {
		return a - (m_dimX * m_dimY);
	}
	return a;
}





