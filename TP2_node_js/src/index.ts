import Benchmark from "./utils/Benchmark";
import {generateCsv, Line} from "./utils/CsvGenerator";
import {BenchmarkResult} from "./utils/Result";
import BenchDataStructure from "./structures/BenchDataStructure";

import MutableStack from "./structures/mutable/Stack";
import MutableQueue from "./structures/mutable/Queue";
import MutableHeap from "./structures/mutable/Heap";
import MutableArray from "./structures/mutable/Array";
import MutableAVL from "./structures/mutable/AVL";

import ImmutableStack from "./structures/immutable/Stack";
import ImmutableQueue from "./structures/immutable/Queue";
import ImmutableHeap from "./structures/immutable/Heap";
import ImmutableArray from "./structures/immutable/Array";
import ImmutableAVL from "./structures/immutable/AVL";

const avgLines = (result: BenchmarkResult, ds: BenchDataStructure<number>): Line[] => {
    const tab: Line[] = [];
    if (ds.insert) {
        tab.push({
            timeInNanoSeconds: result.insertion.avgTime,
            size: result.insertion.times.length,
            type: (ds.mutable ? "MUTABLE" : "IMMUTABLE"),
            action: "AVG-INSERTION",
            struct: ds.name
        });
        console.log(`${ds.name} - INSERTION AVERAGE TIME: ${result.insertion.avgTime}ns`);
    }

    if (ds.pop) {
        tab.push({
            timeInNanoSeconds: result.pop.avgTime,
            size: result.pop.times.length,
            type: (ds.mutable ? "MUTABLE" : "IMMUTABLE"),
            action: "AVG-DELETION",
            struct: ds.name
        });
        console.log(`${ds.name} - DELETION AVERAGE TIME: ${result.pop.avgTime}ns`);
    }

    if (ds.search) {
        tab.push({
            timeInNanoSeconds: result.search.avgTime,
            size: result.search.times.length,
            type: (ds.mutable ? "MUTABLE" : "IMMUTABLE"),
            action: "AVG-SEARCH",
            struct: ds.name
        });
        console.log(`${ds.name} - SEARCH AVERAGE TIME: ${result.search.avgTime}ns`);
    }

    return tab;
};

const insertionLines = (result: BenchmarkResult, ds: BenchDataStructure<number>): Line[] => {
    return result.insertion.times.map((time, index) => {
        return {
            timeInNanoSeconds: time,
            size: index,
            type: (ds.mutable ? "MUTABLE" : "IMMUTABLE"),
            action: "INSERTION",
            struct: ds.name
        }
    });
};

const deletionLines = (result: BenchmarkResult, ds: BenchDataStructure<number>): Line[] => {
    return result.pop.times.map((time, index) => {
        return {
            timeInNanoSeconds: time,
            size: index,
            type: (ds.mutable ? "MUTABLE" : "IMMUTABLE"),
            action: "DELETION",
            struct: ds.name
        }
    });
};

const searchLines = (result: BenchmarkResult, ds: BenchDataStructure<number>): Line[] => {
    return result.search.times.map((time, index) => {
        return {
            timeInNanoSeconds: time,
            size: index,
            type: (ds.mutable ? "MUTABLE" : "IMMUTABLE"),
            action: "SEARCH",
            struct: ds.name
        }
    });
};

const main = () => {
    const dataStructures: BenchDataStructure<number>[] = [];

    dataStructures.push(new MutableAVL<number>());
    dataStructures.push(new ImmutableAVL<number>());

    dataStructures.push(new MutableStack<number>());
    dataStructures.push(new ImmutableStack<number>());

    dataStructures.push(new MutableQueue<number>());
    dataStructures.push(new ImmutableQueue<number>());

    dataStructures.push(new MutableHeap<number>());
    dataStructures.push(new ImmutableHeap<number>());

    dataStructures.push(new MutableArray<number>());
    dataStructures.push(new ImmutableArray<number>());

    let totalResult: Line[] = [];
    dataStructures.forEach(ds => {
        console.log(`\n\n ----- STARTING BENCHMARK FOR ${ds.mutable ? "MUTABLE" : "IMMUTABLE"} ${ds.name} ----- `);
        const bench = new Benchmark(ds);
        const res = bench.runAll();
        console.log(` ----- FINISHED BENCHMARK FOR ${ds.name} ----- `);

        const l1: Line[] = ds.insert ? insertionLines(res, ds) : [];
        const l2: Line[] = ds.search ? searchLines(res, ds) : [];
        const l3: Line[] = ds.pop ? deletionLines(res, ds) : [];
        const avgs = avgLines(res, ds);

        totalResult = totalResult.concat(l1, l2, l3, avgs);
    });

    generateCsv(totalResult, "./benchmarkresult.csv");
};

main();
