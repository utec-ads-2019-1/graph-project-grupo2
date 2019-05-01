#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
    public:
        typedef typename G::N N;
        typedef typename G::E E;
        typedef typename G::edge edge;
        typedef typename G::EdgeSeq EdgeSeq;

        EdgeSeq edges;

    private:
        N data;
        double x;
        double y;

	public:
		Node(N data) : data(data)
		{
			//
		}
		Node(N data, double x, double y) : data(data), x(x), y(y)
		{
			//
		}

		N get_data()
		{
			return (data);
		}
};

#endif
