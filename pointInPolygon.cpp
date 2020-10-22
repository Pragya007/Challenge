#include <iostream> 
using namespace std; 

#define INF 10000 

//To check if point q lies between p and r segment 
bool liesOnSegment(pair<int,int> p, pair<int,int> q, pair<int,int> r) 
{ 
	if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) && 
			q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second)) 
		return true; 
	return false; 
} 

//To find how three points lies 
int orientation(pair<int,int> p, pair<int,int> q, pair<int,int> r) 
{ 
	int val = (q.second - p.second) * (r.first - q.first) - 
			(q.first - p.first) * (r.second - q.second); 

	if (val == 0) return 0; // colinear 
	return (val > 0)? 1: 2; // clock || counterclock wise 
} 

// To tell if line segment 'p1 q1' and 'p2 q2' intersects 
bool dolineSegIntersect(pair<int,int> p1, pair<int,int> q1, pair<int,int> p2, pair<int,int> q2) 
{ 
	int o1 = orientation(p1, q1, p2); 
	int o2 = orientation(p1, q1, q2); 
	int o3 = orientation(p2, q2, p1); 
	int o4 = orientation(p2, q2, q1); 
 
	if (o1 != o2 && o3 != o4) 
		return true; 

	if (o1 == 0 && liesOnSegment(p1, p2, q1)) return true; 

	if (o2 == 0 && liesOnSegment(p1, q2, q1)) return true; 

	if (o3 == 0 && liesOnSegment(p2, p1, q2)) return true; 

	if (o4 == 0 && liesOnSegment(p2, q1, q2)) return true; 

	return false; 
} 

// Returns true if the point p lies inside the polygon 
bool pointIsInsidePolygon(pair<int,int> polygon[], int n, int x, int y) 
{ 
	// Valid polygon
	if (n < 3) return false; 

	// line from (x,y) to infinite 
	pair<int,int> extreme = {INF, y}; 

	// Count intersections of the above line with sides of polygon 
	int count = 0, i = 0; 
	do
	{ 
		int next = (i+1)%n; 

		// Check if the line segment from 'p' to 'extreme' intersects 
		// with the line segment from 'polygon[i]' to 'polygon[next]' 
		if (dolineSegIntersect(polygon[i], polygon[next], {x,y}, extreme)) 
		{ 
			// If the point 'p' is colinear with line segment 'i-next', 
			// then check if it lies on segment. If it lies, return true, 
			// otherwise false 
			if (orientation(polygon[i], {x,y}, polygon[next]) == 0) 
			return liesOnSegment(polygon[i], {x,y}, polygon[next]); 

			count++; 
		} 
		i = next; 
	} while (i != 0); 

	return count&1;  
} 

 
int main() 
{ 
	int vertices;
	cout<<"Enter the number of vertices of polygon:";
	cin >> vertices;
	
	pair<int,int> polygon[vertices];
	for(int i = 0; i < vertices; i++){
	    int a,b;
	    cin >> a >> b;
	    polygon[i] = make_pair(a,b);
	}
	
	cout<<"Enter the coordinate";
	int x,y;
	cin>>x>>y;
	if(pointIsInsidePolygon(polygon, vertices, x, y))
	    cout << "True\n";
	else
        cout << "False\n";
	return 0; 
}
