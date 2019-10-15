import * as fs from "fs";
import {PathLike} from "fs";

const headers = "struct,type,action,size,time";

export interface Line {
    struct: string;
    type: string;
    action: string;
    size: number;
    timeInNanoSeconds: number;
}

export function generateCsv(lines: Line[], filePath: PathLike) {
    let csv = headers + "\n";

    lines.forEach(line => {
       csv += line.struct + "," + line.type + "," + line.action + "," + line.size + "," + line.timeInNanoSeconds + "\n";
    });

    fs.writeFileSync(filePath, csv);
}
