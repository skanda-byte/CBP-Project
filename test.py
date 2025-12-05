from fastapi import FastAPI
from pydantic import BaseModel
from lru_cache import LRUCache
import google.generativeai as genai
from fastapi.middleware.cors import CORSMiddleware
genai.configure(api_key="niggers paste your api key here")

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # for dev; you can restrict later
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
    


cache = LRUCache(50)

class Query(BaseModel):
    query: str
@app.get("/cache")
def show_cache():
    return {"cache": cache.get_all()}


@app.post("/ask")
async def ask_gemini(q: Query):
    key = q.query
    cached = cache.get(key)

    if cached != "":
        return {"answer": cached, "cached": True}

    # No cache → call Gemini
    response = genai.GenerativeModel("models/gemini-2.5-flash").generate_content(key).text
    cache.put(key, response)
    return {"answer": response, "cached": False}
