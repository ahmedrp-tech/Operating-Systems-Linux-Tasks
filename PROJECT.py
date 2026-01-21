# task 1 {Seif}  
# task 2 {Ahmed}
# task 3 {Walaa}
# task 4 {Omnya}
# task 5 {Nada}
# task 6 {Mazen}
# task 7 {Mohamed}
from tabulate import tabulate
'''
# Function to validate positive integer inputs
def get_positive_integer(prompt):
    while True:
        try:
            value = int(input(prompt))
            if value < 0:
                print("Please enter a non-negative integer.")
            else:
                return value
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

# Function to get process details
def get_process_details():
    n = get_positive_integer("Enter the number of processes: ")
    processes = []
    for i in range(n):
        print("-----------------------------------------------------------------------")
        print(f"\nProcess {i + 1}:")
        print("------------------------------------------------------------------------")
        arrival_time = get_positive_integer("Arrival time: ")
        print("----------------------------------------------------")
        burst_time = get_positive_integer("Burst time: ")
        print("-------------------------------------------------------------------------")
        priority = get_positive_integer("Priority (lower value = higher priority): ")
        print("--------------------------------------------------------------------------")
        processes.append({
            'id': i + 1,
            'arrival_time': arrival_time,
            'burst_time': burst_time,
            'priority': priority,
        })
    return processes


'''
def get_process_details():
    step = 0
    n = int(input("Enter the number of processes: "))
    processes = []
    while n: 
        try:
            step += 1
            print("-" * 70)
            print(f"\nProcess {step}:")
            print("-" * 70)
            arrival_time = int(input("Arrival time: "))
            print("-" * 70)
            burst_time = int(input("Burst time: "))
            print("-" * 70)
            priority = int(input("Priority (lower value = higher priority): "))
            print("-" * 70)
        except:
            print("Invalid input. Please enter a valid integer.")
            step -= 1
            continue
        processes.append({
            'id': f'P{step}',
            'arrival_time': arrival_time,
            'burst_time': burst_time,
            'priority': priority,
            })
        n-=1
        
    return processes



# Priority Scheduling (Preemptive) Algorithm
def priority_scheduling_preemptive(processes):
    n = len(processes)
    time = 0
    completed = 0
    waiting_time = [0] * n
    turnaround_time = [0] * n
    response_time = [-1] * n
    burst_remaining = [p['burst_time'] for p in processes]

    while completed != n:
        # Find process with the highest priority that has arrived
        current = -1
        min_priority = float('inf')
        for i in range(n):
            if processes[i]['arrival_time'] <= time and burst_remaining[i] > 0:
                if processes[i]['priority'] < min_priority:
                    min_priority = processes[i]['priority']
                    current = i

        if current != -1:
            # Update response time
            if response_time[current] == -1:
                response_time[current] = time - processes[current]['arrival_time']

            # Execute the current process
            burst_remaining[current] -= 1
            time += 1

            # If process is completed
            if burst_remaining[current] == 0:
                completed += 1
                turnaround_time[current] = time - processes[current]['arrival_time']
                waiting_time[current] = turnaround_time[current] - processes[current]['burst_time']
        else:
            time += 1  # Idle time if no process is ready

    return waiting_time, turnaround_time, response_time

# Function to calculate averages
def calculate_averages(times):
    return sum(times) / len(times) if times else 0

# Main function
def main():
    print("Priority Scheduling (Preemptive)")
    print("Welcome,sir <3")
    processes = get_process_details()

    # Perform scheduling
    waiting_time, turnaround_time, response_time = priority_scheduling_preemptive(processes)

    # Add results to processes
    for i, p in enumerate(processes):
        p['waiting_time'] = waiting_time[i]
        p['turnaround_time'] = turnaround_time[i]
        p['response_time'] = response_time[i]

    # Display results
    print("\nScheduling Results:")
    print(tabulate(processes, headers="keys", tablefmt="grid"))

    # Calculate and display averages
    avg_waiting_time = calculate_averages(waiting_time)
    avg_turnaround_time = calculate_averages(turnaround_time)
    avg_response_time = calculate_averages(response_time)

    print("-" * 70)
    print(f"\nAverage Waiting Time: {avg_waiting_time:.2f}")
    print("-" * 70)
    print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")
    print("-" * 70)
    print(f"Average Response Time: {avg_response_time:.2f}")
    print("-" * 70)

    # Save results to file
    save_results_to_file(processes, avg_waiting_time, avg_turnaround_time, avg_response_time)

# Function to save results to a file
def save_results_to_file(processes, avg_waiting_time, avg_turnaround_time, avg_response_time):
    filename = "scheduling_results.txt"
    with open(filename, "w") as f:
        f.write(tabulate(processes, headers="keys", tablefmt="grid"))
        f.write(f"\n\nAverage Waiting Time: {avg_waiting_time:.2f}")
        f.write(f"\nAverage Turnaround Time: {avg_turnaround_time:.2f}")
        f.write(f"\nAverage Response Time: {avg_response_time:.2f}")
    print(f"\nResults saved to {filename}")
    print("successfully Code <3")

if __name__ == "__main__":
    main()
