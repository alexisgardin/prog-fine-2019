export interface BenchmarkResult {
    insertion: Result;
    pop: Result;
    search: Result;
}

export interface Result {
    avgTime: number;
    times: number[];
}
