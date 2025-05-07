# Vast Expert System for Employee Performance Evaluation

def evaluate_employee(attendance, task_completion, teamwork, punctuality, initiative, communication, deadlines):
    score = 0
    feedback = []

    # Attendance rule
    if attendance >= 95:
        score += 2
        feedback.append("Excellent attendance.")
    elif attendance >= 85:
        score += 1
        feedback.append("Good attendance.")
    else:
        feedback.append("Needs improvement in attendance.")

    # Task completion rule
    if task_completion >= 95:
        score += 3
        feedback.append("Tasks completed with high efficiency.")
    elif task_completion >= 75:
        score += 2
        feedback.append("Tasks mostly completed.")
    else:
        score += 1
        feedback.append("Low task completion rate.")

    # Teamwork rule
    if teamwork == 'excellent':
        score += 2
        feedback.append("Great team player.")
    elif teamwork == 'good':
        score += 1
        feedback.append("Works well in team.")
    else:
        feedback.append("Needs to improve team collaboration.")

    # Punctuality rule
    if punctuality == 'always':
        score += 1
        feedback.append("Always punctual.")
    elif punctuality == 'sometimes':
        feedback.append("Occasionally late.")
    else:
        feedback.append("Frequently late.")

    # Initiative rule
    if initiative == 'high':
        score += 2
        feedback.append("Takes strong initiative.")
    elif initiative == 'moderate':
        score += 1
        feedback.append("Shows some initiative.")
    else:
        feedback.append("Rarely takes initiative.")

    # Communication skills
    if communication == 'excellent':
        score += 2
        feedback.append("Excellent communication skills.")
    elif communication == 'good':
        score += 1
        feedback.append("Good communicator.")
    else:
        feedback.append("Needs improvement in communication.")

    # Meeting deadlines
    if deadlines == 'always':
        score += 2
        feedback.append("Always meets deadlines.")
    elif deadlines == 'mostly':
        score += 1
        feedback.append("Meets deadlines most of the time.")
    else:
        feedback.append("Frequently misses deadlines.")

    # Final decision
    if score >= 10:
        result = "Performance Rating: ⭐ EXCELLENT"
    elif score >= 7:
        result = "Performance Rating: ✅ GOOD"
    elif score >= 5:
        result = "Performance Rating: ⚠️ AVERAGE"
    else:
        result = "Performance Rating: ❌ POOR - Needs Immediate Attention"

    return result, feedback

print("---- Employee Performance Evaluation ----")

attendance = int(input("Enter attendance percentage (0-100): "))
task_completion = int(input("Enter task completion percentage (0-100): "))
teamwork = input("Rate teamwork (excellent/good/poor): ").strip().lower()
punctuality = input("Punctuality (always/sometimes/rarely): ").strip().lower()
initiative = input("Initiative (high/moderate/low): ").strip().lower()
communication = input("Communication (excellent/good/poor): ").strip().lower()
deadlines = input("Meeting Deadlines (always/mostly/rarely): ").strip().lower()

rating, comments = evaluate_employee(attendance, task_completion, teamwork, punctuality, initiative, communication, deadlines)

print("\n--- Evaluation Result ---")
for comment in comments:
    print("-", comment)
print("\n", rating)
