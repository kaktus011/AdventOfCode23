import fs from 'fs';

const file = 'input.txt';
const lines = fs.readFileSync(file, 'utf-8').trim().split('\n');

function ParseData(data) {
    const maxColors = {
        'red' : 12,
        'green' : 13,
        'blue' : 14
    };

    return lines.map( line => {
        return line = line.split(': ')[1].split('; ').map(set => {
            const turns = set.split(', ');
            return turns.every( turn => {
                const [number, color] = turn.split(' ');
                return maxColors[color] >= Number(number);
            });
        }).every(k => k);
    }).reduce((sum, value, indx) => {
        return value? sum + (indx + 1): sum; }, 0);
}



console.log(ParseData(lines));
