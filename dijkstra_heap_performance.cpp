// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// modified version of Douglas Gregor and Andrew Lumsdaine 
// by Guilherme Torres Castro
// this version compare binary_heap vs fibonacci_heap 
// for dijkstra shortest path
	
#define BOOST_GRAPH_DIJKSTRA_TESTING

// use a modified version of dijkstra_shortest_paths.hpp
#include "dijkstra_shortest_paths.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/timer.hpp>
#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <boost/random/uniform_int.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/detail/lightweight_test.hpp>


using namespace boost;


void test(int n)
{
  std::cout<<n<<"\n";
  double fibonacci_heap_time = 0.0;
  double binary_heap_time = 0.0;
  double relaxed_heap_time = 0.0;
  double d_ary_heap_time = 0.0;
  int numberOftests = 50;
  unsigned m = (n * (n -1)) /2;
  std::cout<<m<<"\n";
  return;
  for (int i = 0;i< numberOftests;i++){
	  
	  
	  int seed =  n * 0x231;

	  // Build random graph
	  typedef adjacency_list<vecS, vecS, directedS, no_property,property<edge_weight_t, double> > Graph;
	  //std::cout << "Generating graph...";
	  std::cout.flush();
	  minstd_rand gen(seed);
	  double p = double(m)/(double(n)*double(n));
	  Graph g(erdos_renyi_iterator<minstd_rand, Graph>(gen, n, p), erdos_renyi_iterator<minstd_rand, Graph>(), n);
	  //std::cout << n << " vertices, " << num_edges(g) << " edges.\n";
	  uniform_real<double> rand01(0.0, 1.0);
	  graph_traits<Graph>::edge_iterator ei, ei_end;
	  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
		put(edge_weight, g, *ei, rand01(gen));

	  std::vector<double> binary_heap_distances(n);
	  std::vector<double> fibonacci_heap_distances(n);
	  std::vector<double> relaxed_heap_distances(n);
	  std::vector<double> d_ary_heap_distances(n);
	  
	  dijkstra_heap = fibonacci_kind;
	  timer t;  
	  dijkstra_shortest_paths(g, vertex(0, g),distance_map(&fibonacci_heap_distances[0])); 
	  fibonacci_heap_time += t.elapsed();
	  
	  dijkstra_heap = binary_kind;
	  t.restart();
	  dijkstra_shortest_paths(g, vertex(0, g),distance_map(&binary_heap_distances[0]));
	  binary_heap_time += t.elapsed();
	  
	  dijkstra_heap = relaxed_kind;
	  t.restart();
	  dijkstra_shortest_paths(g, vertex(0, g),distance_map(&relaxed_heap_distances[0]));
	  relaxed_heap_time += t.elapsed();
	  
	  dijkstra_heap = d_ary_kind;
	  t.restart();
	  dijkstra_shortest_paths(g, vertex(0, g),distance_map(&d_ary_heap_distances[0]));
	  d_ary_heap_time += t.elapsed();
	  
  }
  std::cout<<(fibonacci_heap_time/numberOftests)<<" "<<(binary_heap_time/numberOftests)<<" "<<(relaxed_heap_time/numberOftests)<<" "<<(d_ary_heap_time/numberOftests)<<"\n";

}

int main(){
	for (int i =1;i<9;i++){
		test(i * 1000);
	}
}
