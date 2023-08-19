GOOGLE MAP USAGE FOR OUR STICK

//we use the  api call by the google map api using python


import googlemaps

# Replace 'YOUR_API_KEY' with your actual Google Maps API key
API_KEY = 'YOUR_API_KEY'
gmaps = googlemaps.Client(key=API_KEY)

def get_current_location():
    # Fetch current location data (latitude and longitude)
    current_location = gmaps.geolocate()
    return current_location['location']['lat'], current_location['location']['lng']

while True:
    # Get current location
    lat, lng = get_current_location()
    print("Current Latitude:", lat)
    print("Current Longitude:", lng)
    # Further processing or interaction with the Arduino can be implemented here
