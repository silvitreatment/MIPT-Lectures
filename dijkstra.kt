import java.util.*

const val INF = Int.MAX_VALUE

fun dijkstra(n : Int, graph : List<MutableList<Pair<Int, Int>>>, start : Int) : IntArray {
    val dist = IntArray(n) { INF }
    dist[start] = 0
    val pq = PriorityQueue<Pair<Int, Int>>(compareBy {it.first })
    pq.add(0 to start)

    while (pq.isNotEmpty()) {
        val (curDist, u) = pq.poll()
        if (curDist > dist[u]) continue

        for ((v, weight) in graph[u]) {
            val newDist = dist[u] + weight
            if (newDist < dist[v]) {
                dist[v] = newDist
                pq.add(newDist to v)
            }
        }
    } 
    return dist
}

fun main() {
    val n = 5
    val m = 6
    val graph = List(n) { mutableListOf<Pair<Int, Int>>()}

     val edges = listOf(
        Triple(0, 1, 2),
        Triple(0, 2, 4),
        Triple(1, 2, 1),
        Triple(1, 3, 7),
        Triple(2, 4, 3),
        Triple(3, 4, 1)
    )
    for ((u, v, w) in edges) {
        graph[u].add(v to w)
        graph[v].add(u to w)
    }
    val start = 0
    val distances = dijkstra(n, graph, start)
    println("Кратчайшие расстояния от вершины $start:")
    println(distances.joinToString(" ") { d -> if (d == INF) "INF" else d.toString() })

}