import gradio as gr
from nltk.chat.util import Chat, reflections
import re

# Menu for the chatbot
menu = {
    "Dosa": 50,
    "Idli": 30,
    "Pizza": 120,
    "Pasta": 100,
    "Chai": 20
}

# Pairs of patterns and responses
pairs = [
    [r"hi|hello|hey", 
     ["Hello! How can I help you today?"]], 

    [r".*menu.*",
     ["Here is our menu:\n" + "\n".join([f"{item}: ₹{price}" for item, price in menu.items()])]],

    [r".*order.*",
     ["Sure! What would you like to order? (Example: say 2 servings of Pizza)"]],

    [r".*special.*",
     ["Our special dish is called Chef's special Pasta."]],

    [r".*(sweet|dessert|ice-cream).*",
     ["Bringing you sweet sir/mam.", "Bringing your dessert sir/mam", "Bringing you ice-cream sir/mam"]],

    [r"thank you|thanks",
     ["You are welcome!"]],

    [r"bye|exit|quit",
     ["Thanks and have a nice day"]],

    # Fallback for unrecognized input
    [r"(.*)", 
     ["Sorry, I didn't get it. Can you please rephrase it?"]]
]

# Create chatbot
chatbot = Chat(pairs, reflections)

# Function to calculate the order cost
def calc_order_cost(message):
    # (\d+) group1 captures one or more digits
    # \s for matching whitespace
    # \b makes sure you capture full word not substring
    # (\w+) group2 capturs last word
    # you can also use less greedy approch
    # match = re.search(r"(\d+)\s+.*\b(\w+)", message, re.IGNORECASE)

    match = re.search(r"(\d+)\s+.*\b(\w+)", message, re.IGNORECASE)
    if match:
        count = int(match.group(1))
        item = match.group(2).title()  # Capitalize the first letter of the item
        if item in menu:
            cost = count * menu[item]
            return f"Ordered {count} {item}(s). Total cost is ₹{cost}."
        else:
            return "Item not available."
    return None

# Gradio response function
def respond(message, history):
    # Try to get order response first
    order_response = calc_order_cost(message)
    if order_response:
        return order_response
    # Otherwise, respond via the chatbot
    return chatbot.respond(message)

# Launch Gradio app
demo = gr.ChatInterface(
    fn=respond,
    title="PICT Restro",
    description="Ask menu and place an order.",
    theme="soft"
)

demo.launch()

# simple code
# import gradio as gr
# from nltk.chat.util import Chat, reflections

# # Menu for the chatbot
# menu = {
#     "Dosa": 50,
#     "Idli": 30,
#     "Pizza": 120,
#     "Pasta": 100,
#     "Chai": 20
# }

# # Pairs of patterns and responses
# pairs = [
#     [r"hi|hello|hey", 
#      ["Hello! How can I help you today?"]], 

#     [r".*menu.*",
#      ["Here is our menu:\n" + "\n".join([f"{item}: ₹{price}" for item, price in menu.items()])]],

#     [r".*order.*",
#      ["Sure! What would you like to order? Just let me know your dish."]],

#     [r".*special.*",
#      ["Our special dish is called Chef's special Pasta."]],

#     [r".*(sweet|dessert|ice-cream).*",
#      ["Bringing you sweet sir/mam.", "Bringing your dessert sir/mam", "Bringing you ice-cream sir/mam"]],

#     [r"thank you|thanks",
#      ["You are welcome!"]],

#     [r"bye|exit|quit",
#      ["Thanks and have a nice day!"]],

#     [r"(.*)", 
#      ["Sorry, I didn't get it. Can you please rephrase it?"]]
# ]

# # Create chatbot
# chatbot = Chat(pairs, reflections)

# # Gradio response function
# def respond(message, history):
#     return chatbot.respond(message)

# # Launch Gradio app
# demo = gr.ChatInterface(
#     fn=respond,
#     title="PICT Restro",
#     description="Ask menu and place an order.",
#     theme="soft"
# )

# demo.launch()
