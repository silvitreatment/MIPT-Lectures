import java.io.BufferedReader
import java.io.InputStreamReader


fun topologicalSort(n : Int, graph: Array<List<Int>>) : List<Int> {
    val visited = BooleanArray(n)
    val result = mutableListOf<Int>()

    fun dfs(u : Int) {
        visited[u] = true
        for (v in graph[u]) {
            if (!visited[v]) {
                dfs(v)
            }
        }
        result.add(u)
    }

    for (i in 0 until n) {
        if (!visited[i]) {
            dfs(i)
        }
    }
    result.reverse()
    return result
}

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    // Пример чтения: первая строка содержит n и m
    val (n, m) = reader.readLine().split(' ').map { it.toInt() }

    // Создаём список смежности для ориентированного графа (индексация с 0 до n-1)
    val graph = Array(n) { mutableListOf<Int>() }
    repeat(m) {
        val (u, v) = reader.readLine().split(' ').map { it.toInt() }
        // Предполагается, что ребро направленное: u -> v
        // Если индексация входных данных с 1, то использовать: graph[u - 1].add(v - 1)
        graph[u].add(v)
    }

    val order = topologicalSort(n, graph)
    // Выводим топологический порядок
    println(order.joinToString(" "))
}