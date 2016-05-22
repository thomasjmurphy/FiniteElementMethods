class Node
{
    public:
    double x;
    double y;
    vector<*Element> elements;
    Node(double x, double y) : x(x), y(x) {}
};
class Element
{
    public:
    vector<*Node> nodes;   
    Element(Node *n1, Node *n1, Node *n3)
    {
        vector<*Nodes> vec = {n1, n2, n3};
        nodes = vec;
    }
};

class Mesh
{
    public:
    vector<*Node> nodes;
    vector<*Element> elements;
    halfMeshSize()
    {
        int numElems = elements.size();
        while(numElems)
        {
            Node *avgnode0 = new Node((this.elements[0]->nodes[0]->x +this.elements[1]->nodes[1]->x)/2,(this.elements[0]->nodes[0]->y + this.elements[0]->nodes[1]->y)/2);
            
            Node *avgnode1 = new Node((this.elements[0]->nodes[1]->x +this.elements[1]->nodes[1]->x)/2,(this.elements[0]->nodes[1]->y + this.elements[0]->nodes[2]->y)/2);
            
            Node *avgnode2 = new Node((this.elements[0]->nodes[1]->x +this.elements[1]->nodes[1]->x)/2,(this.elements[0]->nodes[1]->y + this.elements[0]->nodes[2]->y)/2);
            
            Element *elem1 = new Element(nodes[0], avgnode0, avgnode2);
            Element *elem2 = new Element(avgnode1, nodes[1], avgnode1);
            Element *elem3 = new Element(avgnode0, avgnode2, avgnode1);
            Element *elem4 = new Element(avgnode2, avgnode1, nodes[2]);
            
        }
    }
}


class Poly2d  //coeff order  1,x,y,xy
{
    public:
    vector<double> coeff;
    Poly2d(vector<double> &coeff) : deg(deg), coeff(coeff) {}
    vector<Poly2d> grad()
    {
        vector<double> coeffX = this.coeff; 
        coeffX[0] = coeff[1];
        coeffX[1] = 0;
        coeffX[2] = coeff[3];
        coeffX[3] = 0;
        
        vector<double> coeffY = this.coeff; 
        coeffX[0] = coeff[2];
        coeffX[1] = coeff[3];
        coeffX[2] = 0;
        coeffX[3] = 0;
        
        vector<Poly2d> grad;
        grad.push_back(Poly2d(coeffX));
        grad.push_back(Poly2d(coeffY));
        
        return grad;
    }
    
    Poly2d operator*(const Poly2d &poly) //only need to multiply (c1+c2x)*(c3+c4y)
    {
        vector<double> vec = {0,0,0,0};
        Poly2d product(vec);
        product.coeff[0] = this.coeff[0]*poly.coeff[0];
        product.coeff[1] = this.coeff[0]*poly.coeff[1] + this.coeff[1]*poly.coeff[0];
        product.coeff[2] = this.coeff[0]*poly.coeff[2] + this.coeff[2]*poly.coeff[0];
        product.coeff[3] = this.coeff[2]*poly.coeff[1] + this.coeff[1]*poly.coeff[2];
        return product;
    }
};

double Integrate(Poly2d poly) //Integrate on the reference element (0,0),(1,0),(0,1)
{
    double sum = 0;
    sum += poly.coeff[0]*1.0/2;
    sum += poly.coeff[1]*1.0/3;
    sum += poly.coeff[2]*1.0/3;
    sum += poly.coeff[3]*1.0/8;
    return sum;
}
