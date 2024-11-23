void fbpad_fbink_start(void);
void fbpad_fbink_stop(void);
void *fbpad_fbink_worker(void *p);
void fbpad_fbink_refresh(void);

// Right now we just refresh the whole framebuffer at every update
// We can do way better: we could communicate small rectangles to
// fbink_worker, but the math for this involves math I'm too lazy
// for right now.
const FBInkConfig fbpad_fbink_einkConfig = { 0 }; 
const struct timespec fbpad_fbink_cooldown_ts = { 0, 30*1000*1000 };
