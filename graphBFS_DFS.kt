import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.ArrayDeque


fun dfsRecursive(node: Int, compNum: Int, visited: IntArray, graph: Array<out List<Int>>) {
    visited[node] = compNum
    for (neighbor in graph[node]) {
        if (visited[neighbor] == 0) {
            dfsRecursive(neighbor, compNum, visited, graph)
        }
    }
}



fun dfsIterative(start: Int, compNum: Int, visited: IntArray, graph: Array<out List<Int>>) {
    val stack = ArrayDeque<Int>()
    stack.push(start)
    visited[start] = compNum

    while (stack.isNotEmpty()) {
        val node = stack.pop()
        for (neighbor in graph[node]) {
            if (visited[neighbor] == 0) {
                visited[neighbor] = compNum
                stack.push(neighbor)
            }
        }
    }
}

fun bfs(start: Int, compNum: Int, visited: IntArray, graph: Array<out List<Int>>) {
    val queue = ArrayDeque<Int>()
    queue.add(start)
    visited[start] = compNum

    while (queue.isNotEmpty()) {
        val node = queue.removeFirst()
        for (neighbor in graph[node]) {
            if (visited[neighbor] == 0) {
                visited[neighbor] = compNum
                queue.add(neighbor)
            }
        }
    }
}

fun main() {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val (n, m) = reader.readLine().split(' ').map { it.toInt() }

    // Готовим граф (список смежности), индексация с 1 по n
    val graph = Array(n + 1) { mutableListOf<Int>() }
    repeat(m) {
        val (u, v) = reader.readLine().split(' ').map { it.toInt() }
        graph[u].add(v)
        graph[v].add(u)
    }

    val visited = IntArray(n + 1)
    var ans = 0

    // Обходим вершины и находим компоненты
    for (i in 1..n) {
        if (visited[i] == 0) {
            ans++
            // Выбирайте нужный метод обхода:
            // dfsRecursive(i, ans, visited, graph)
            // dfsIterative(i, ans, visited, graph)
            bfs(i, ans, visited, graph)
        }
    }

    // Формируем вывод
    val sb = StringBuilder()
    sb.appendLine(ans)
    for (i in 1..n) {
        sb.append(visited[i]).append(' ')
    }
    println(sb)
}
